#pragma once

#include <string>

namespace Engine {

class GraphicsContext;

class Texture {
public:
	Texture(const std::string& path);
	Texture(void* data, int width, int height, int pitch);
	~Texture();

	void Render(GraphicsContext* context, float x, float y, float w, float h);

	int GetWidth() const { return m_width; };
	int GetHeight() const { return m_height; };
	void* GetPixelData() const { return m_data; };

private:
	std::string m_filePath;

	unsigned char* m_data = nullptr;

	int m_width = 0;
	int m_height = 0;
	int m_channels = 0;
};

} // namespace Engine