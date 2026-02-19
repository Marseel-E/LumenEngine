#include "MetalTexture.hpp"

#include "LumenEngine/core/Logger.hpp"

namespace Engine {

MetalTexture::MetalTexture(MTL::Device* device, const Texture& texture) {
	MTL::TextureDescriptor* textureDesc = MTL::TextureDescriptor::alloc()->init();

	textureDesc->setPixelFormat(MTL::PixelFormatBGRA8Unorm);
	textureDesc->setWidth(texture.GetWidth());
	textureDesc->setHeight(texture.GetHeight());

	textureDesc->setStorageMode(MTL::StorageModeManaged);
	textureDesc->setUsage(MTL::TextureUsageShaderRead);

	m_texture = device->newTexture(textureDesc);

	NS::UInteger bytesPerRow = (NS::UInteger)texture.GetWidth() * 4;

	MTL::Region region = MTL::Region::Make2D(0, 0, texture.GetWidth(), texture.GetHeight());

	m_texture->replaceRegion(region, 0, texture.GetPixelData(), bytesPerRow);

	textureDesc->release();
};

MetalTexture::~MetalTexture() {
	if (m_texture) m_texture->release();
};

} // namespace Engine