#pragma once

#include <Metal/Metal.hpp>

#include "LumenEngine/graphics/Texture.hpp"

namespace Engine {

class MetalTexture {
public:
	MetalTexture(MTL::Device* device, const Texture& texture);
	~MetalTexture();

	MTL::Texture* GetMTLTexture() const { return m_texture; };

private:
	MTL::Texture* m_texture = nullptr;
};

} // namespace Engine