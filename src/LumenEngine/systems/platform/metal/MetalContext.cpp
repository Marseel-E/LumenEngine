#define NS_PRIVATE_IMPLEMENTATION
#define CA_PRIVATE_IMPLEMENTATION
#define MTL_PRIVATE_IMPLEMENTATION

#include "MetalContext.hpp"

#include <SDL2/SDL.h>

#include <fstream>
#include <map>
#include <sstream>

#include "LumenEngine/core/Logger.hpp"
#include "LumenEngine/core/Math.hpp"
#include "LumenEngine/systems/Window.hpp"
#include "MetalTexture.hpp"

namespace Engine {

MetalContext::MetalContext(Window& window) {};

MetalContext::~MetalContext() {
	Shutdown();
};

bool MetalContext::Init(Window& window) {
	m_device = MTL::CreateSystemDefaultDevice();
	if (!m_device) {
		Logger::Error("Failed to create Metal Device");

		return false;
	};
	Logger::Info("Metal Device Created!");

	m_commandQueue = m_device->newCommandQueue();

	SDL_Window* sdlWindow = static_cast<SDL_Window*>(window.GetNativeWindow());
	SDL_MetalView metalView = SDL_Metal_CreateView(sdlWindow);

	if (metalView == nullptr) {
		Logger::Error("Failed to create SDL metal view");

		return false;
	};

	m_metalLayer = static_cast<CA::MetalLayer*>(SDL_Metal_GetLayer(metalView));

	if (!m_metalLayer) {
		Logger::Error("Failed to create Metal Layer.");

		return false;
	};

	m_metalLayer->setDevice(m_device);
	m_metalLayer->setPixelFormat(MTL::PixelFormatBGRA8Unorm);

	m_clearColor = MTL::ClearColor::Make(0.0, 0.0, 0.0, 1.0);

	if (!CreatePipeline()) {
		return false;
	};

	m_cameraBuffer = m_device->newBuffer(sizeof(Mat4), MTL::ResourceStorageModeShared);

	MTL::SamplerDescriptor* samplerDesc = MTL::SamplerDescriptor::alloc()->init();
	samplerDesc->setMinFilter(MTL::SamplerMinMagFilterNearest);
	samplerDesc->setMagFilter(MTL::SamplerMinMagFilterNearest);
	samplerDesc->setSAddressMode(MTL::SamplerAddressModeRepeat);
	samplerDesc->setTAddressMode(MTL::SamplerAddressModeRepeat);

	m_samplerState = m_device->newSamplerState(samplerDesc);
	samplerDesc->release();

	MTL::TextureDescriptor* texDesc = MTL::TextureDescriptor::alloc()->init();
	texDesc->setPixelFormat(MTL::PixelFormatBGRA8Unorm);
	texDesc->setWidth(1);
	texDesc->setHeight(1);
	texDesc->setStorageMode(MTL::StorageModeManaged);
	texDesc->setUsage(MTL::TextureUsageShaderRead);

	m_whiteTexture = m_device->newTexture(texDesc);
	texDesc->release();

	uint8_t pixel[4] = {255, 255, 255, 255};
	MTL::Region region = MTL::Region::Make2D(0, 0, 1, 1);
	m_whiteTexture->replaceRegion(region, 0, pixel, 4);

	// m_currentTexture = m_whiteTexture;

	return true;
};

void MetalContext::Shutdown() {
	if (m_device) {
		m_device->release();
		m_device = nullptr;
	};

	if (m_commandQueue) {
		m_commandQueue->release();
		m_commandQueue = nullptr;
	};

	if (m_pipelineState) {
		m_pipelineState->release();
		m_pipelineState = nullptr;
	};

	if (m_vertexBuffer) {
		m_vertexBuffer->release();
		m_vertexBuffer = nullptr;
	};

	if (m_cameraBuffer) {
		m_cameraBuffer->release();
		m_cameraBuffer = nullptr;
	};
};

void MetalContext::BeginFrame() {
	m_currentDrawable = m_metalLayer->nextDrawable();

	m_drawCalls.clear();
	m_batchVertices.clear();

	MetalDrawCall firstCall;
	firstCall.vertexStart = 0;
	firstCall.vertexCount = 0;
	firstCall.texture = m_whiteTexture;
	m_drawCalls.push_back(firstCall);

	m_currentTexture = m_whiteTexture;
};

void MetalContext::EndFrame() {
	if (!m_currentDrawable || m_batchVertices.empty()) return;

	MTL::CommandBuffer* cmdBuffer = m_commandQueue->commandBuffer();
	MTL::RenderPassDescriptor* passDesc = MTL::RenderPassDescriptor::renderPassDescriptor();
	auto* colorAttachment = passDesc->colorAttachments()->object(0);

	colorAttachment->setTexture(m_currentDrawable->texture());
	colorAttachment->setLoadAction(MTL::LoadActionClear);
	colorAttachment->setStoreAction(MTL::StoreActionStore);
	colorAttachment->setClearColor(m_clearColor);

	MTL::RenderCommandEncoder* encoder = cmdBuffer->renderCommandEncoder(passDesc);

	if (m_pipelineState) {
		encoder->setRenderPipelineState(m_pipelineState);
		encoder->setVertexBuffer(m_cameraBuffer, 0, 1);

		size_t totalSize = m_batchVertices.size() * sizeof(Vertex);
		MTL::Buffer* vBuffer = m_device->newBuffer(m_batchVertices.data(), totalSize, MTL::ResourceStorageModeShared);
		encoder->setVertexBuffer(vBuffer, 0, 0);

		for (const auto& call : m_drawCalls) {
			if (call.vertexCount == 0) continue;

			encoder->setFragmentTexture(call.texture, 0);
			encoder->setFragmentSamplerState(m_samplerState, 0);

			encoder->drawPrimitives(MTL::PrimitiveTypeTriangle, (NS::UInteger)call.vertexStart,
									(NS::UInteger)call.vertexCount);
		}

		vBuffer->release();
	};

	encoder->endEncoding();
	cmdBuffer->presentDrawable(m_currentDrawable);
	cmdBuffer->commit();
	passDesc->release();

	m_drawCalls.clear();
	m_batchVertices.clear();
};

void MetalContext::Clear(float r, float g, float b, float a) {
	m_clearColor = MTL::ClearColor::Make(r, g, b, a);
};

void MetalContext::SetViewport(int width, int height) {
	if (m_metalLayer) {
		m_metalLayer->setDrawableSize(CGSizeMake(static_cast<double>(width), static_cast<double>(height)));
	};
};

bool MetalContext::CreatePipeline() {
	std::ifstream file("src/LumenEngine/systems/platform/metal/Shaders.metal");
	if (!file.is_open()) {
		Logger::Error("Failed to opejn shaders.metal");

		return false;
	};

	std::stringstream buffer;
	buffer << file.rdbuf();
	std::string source = buffer.str();

	NS::String* sourceNS = NS::String::string(source.c_str(), NS::UTF8StringEncoding);

	NS::Error* error = nullptr;
	MTL::CompileOptions* options = MTL::CompileOptions::alloc()->init();
	MTL::Library* library = m_device->newLibrary(sourceNS, options, &error);

	if (!library) {
		Logger::Error("Failed to compile shaders", error->localizedDescription()->utf8String());

		return false;
	};

	MTL::Function* vertFunc = library->newFunction(NS::String::string("vertexMain", NS::UTF8StringEncoding));
	MTL::Function* fragFunc = library->newFunction(NS::String::string("fragmentMain", NS::UTF8StringEncoding));

	if (!vertFunc || !fragFunc) {
		Logger::Error("Failed to find shader functions.");

		return false;
	};

	MTL::RenderPipelineDescriptor* psoDesc = MTL::RenderPipelineDescriptor::alloc()->init();
	psoDesc->setVertexFunction(vertFunc);
	psoDesc->setFragmentFunction(fragFunc);

	auto* colorAttachment = psoDesc->colorAttachments()->object(0);
	colorAttachment->setPixelFormat(MTL::PixelFormatBGRA8Unorm);

	colorAttachment->setBlendingEnabled(true);

	colorAttachment->setRgbBlendOperation(MTL::BlendOperationAdd);
	colorAttachment->setSourceRGBBlendFactor(MTL::BlendFactorSourceAlpha);
	colorAttachment->setDestinationRGBBlendFactor(MTL::BlendFactorOneMinusSourceAlpha);

	colorAttachment->setAlphaBlendOperation(MTL::BlendOperationAdd);
	colorAttachment->setSourceAlphaBlendFactor(MTL::BlendFactorOne);
	colorAttachment->setDestinationAlphaBlendFactor(MTL::BlendFactorOneMinusSourceAlpha);

	m_pipelineState = m_device->newRenderPipelineState(psoDesc, &error);
	if (!m_pipelineState) {
		Logger::Error("Failed to create pipeline state", error->localizedDescription()->utf8String());

		return false;
	};

	vertFunc->release();
	fragFunc->release();
	library->release();
	psoDesc->release();
	options->release();
	sourceNS->release();

	Logger::Info("Render pipeline created successfully!");

	return true;
};

void MetalContext::SetCamera(const Mat4& viewProjection) {
	if (m_cameraBuffer) {
		memcpy(m_cameraBuffer->contents(), &viewProjection, sizeof(Mat4));
	};
};

void MetalContext::DrawRect(float x, float y, float width, float height, float r, float g, float b, float a) {
	float left = x;
	float right = x + width;
	float top = y;
	float bottom = y + height;

	m_batchVertices.push_back({{left, top, 0.0f, 1.0f}, {r, g, b, a}, {0.0f, 0.0f}});
	m_batchVertices.push_back({{right, top, 0.0f, 1.0f}, {r, g, b, a}, {1.0f, 0.0f}});
	m_batchVertices.push_back({{left, bottom, 0.0f, 1.0f}, {r, g, b, a}, {0.0f, 1.0f}});

	m_batchVertices.push_back({{right, top, 0.0f, 1.0f}, {r, g, b, a}, {1.0f, 0.0f}});
	m_batchVertices.push_back({{right, bottom, 0.0f, 1.0f}, {r, g, b, a}, {1.0f, 1.0f}});
	m_batchVertices.push_back({{left, bottom, 0.0f, 1.0f}, {r, g, b, a}, {0.0f, 1.0f}});

	if (!m_drawCalls.empty()) {
		m_drawCalls.back().vertexCount += 6;
	} else {
		Logger::Error("DrawRect called without an active DrawCall!");
	};
};

void MetalContext::UploadMesh(Vertex* data, int vertexCount) {
	size_t bufferSize = vertexCount * sizeof(Vertex);

	if (m_vertexBuffer) {
		m_vertexBuffer->release();
	};

	m_vertexBuffer = m_device->newBuffer(data, bufferSize, MTL::ResourceStorageModeShared);

	Logger::Info("Mesh uploaded to GPU");
};

void MetalContext::BindTexture(Texture* texture) {
	MTL::Texture* metalHandle = m_whiteTexture;

	if (texture) {
		static std::map<Texture*, MetalTexture*> textureCache;

		if (textureCache.find(texture) == textureCache.end()) {
			textureCache[texture] = new MetalTexture(m_device, *texture);
		};

		metalHandle = textureCache[texture]->GetMTLTexture();
	};

	if (m_drawCalls.empty() || m_drawCalls.back().texture != metalHandle) {
		MetalDrawCall newCall;
		newCall.vertexStart = (uint32_t)m_batchVertices.size();
		newCall.vertexCount = 0;
		newCall.texture = metalHandle;
		m_drawCalls.push_back(newCall);
	};

	m_currentTexture = metalHandle;
};

} // namespace Engine