#pragma once

#include <metal-cpp/Metal/Metal.hpp>
#include <metal-cpp/QuartzCore/CAMetalLayer.hpp>
#include <metal-cpp/QuartzCore/QuartzCore.hpp>
#include <vector>

#include "LumenEngine/graphics/GraphicsContext.hpp"

namespace Engine {

class MetalContext : public GraphicsContext {
public:
	MetalContext(Window& window);
	~MetalContext() override;

	bool Init(Window& window) override;

	void Shutdown() override;
	void BeginFrame() override;
	void EndFrame() override;
	void Clear(float r, float g, float b, float a) override;
	void SetViewport(int width, int height) override;
	void SetCamera(const Mat4& viewProjection) override;
	void UploadMesh(Vertex* data, int vertexCount) override;
	void DrawRect(float x, float y, float width, float height, float r, float g, float b, float a) override;
	void BindTexture(Texture* texture) override;

private:
	MTL::Device* m_device = nullptr;
	MTL::CommandQueue* m_commandQueue = nullptr;

	CA::MetalLayer* m_metalLayer = nullptr;
	CA::MetalDrawable* m_currentDrawable = nullptr;
	MTL::ClearColor m_clearColor;

	MTL::RenderPipelineState* m_pipelineState = nullptr;

	MTL::Buffer* m_vertexBuffer = nullptr;
	MTL::Buffer* m_cameraBuffer = nullptr;

	std::vector<Vertex> m_batchVertices;

	MTL::Texture* m_currentTexture = nullptr;
	MTL::SamplerState* m_samplerState = nullptr;
	MTL::Texture* m_whiteTexture = nullptr;

	bool CreatePipeline();

	struct MetalDrawCall {
		uint32_t vertexStart;
		uint32_t vertexCount;
		MTL::Texture* texture;
	};

	std::vector<MetalDrawCall> m_drawCalls;
};

} // namespace Engine