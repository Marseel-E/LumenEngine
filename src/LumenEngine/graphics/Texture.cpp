#include "Texture.hpp"

#include "GraphicsContext.hpp"
#include "LumenEngine/core/Logger.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image/stb_image.h"

namespace Engine {

Texture::Texture(const std::string& path) : m_filePath(path) {
	// stbi_set_flip_vertically_on_load(1);

	m_data = stbi_load(path.c_str(), &m_width, &m_height, &m_channels, 4);

	if (m_data) {
		Logger::Info("Loaded texture: " + path);
	} else {
		Logger::Error("Failed to load texture", path);
	};
};

Texture::Texture(void* data, int width, int height, int pitch)
	: m_data(nullptr), m_width(width), m_height(height), m_channels(4) {
	size_t size = width * height * 4;
	m_data = (unsigned char*)malloc(size);
	unsigned char* src = (unsigned char*)data;

	for (int y = 0; y < height; y++) {
		unsigned char* srcRow = src + (y * pitch);
		unsigned char* dstRow = m_data + (y * width * 4);

		for (int x = 0; x < width; x++) {
			int i = x * 4;
			dstRow[i + 0] = srcRow[i + 2]; // Blue  <- Red
			dstRow[i + 1] = srcRow[i + 1]; // Green <- Green
			dstRow[i + 2] = srcRow[i + 0]; // Red   <- Blue
			dstRow[i + 3] = srcRow[i + 3]; // Alpha <- Alpha
		}
	}
};

Texture::~Texture() {
	if (m_data) {
		stbi_image_free(m_data);
	};
};

void Texture::Render(GraphicsContext* context, float x, float y, float w, float h) {
	context->BindTexture(this);
	context->DrawRect(x, y, w, h, 1.0f, 1.0f, 1.0f, 1.0f);
};

} // namespace Engine