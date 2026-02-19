#pragma once

#include "LumenEngine/core/Math.hpp"

namespace Engine {
class Window;
}

namespace Engine {

struct Vertex {
	float position[4]; // x, y, z, w
	float color[4];	   // r, g, b, a
	float uv[2];	   // u, v
	float padding[2];  // 8 bytes (pad to 48 bytes)
};

class GraphicsContext {
public:
	virtual ~GraphicsContext() = default;

	virtual bool Init(Window& window) = 0;

	virtual void Shutdown() = 0;
	virtual void BeginFrame() = 0;
	virtual void EndFrame() = 0;
	virtual void Clear(float r, float g, float b, float a) = 0;
	virtual void SetViewport(int width, int height) = 0;
	virtual void SetCamera(const Mat4& viewProjection) = 0;
	virtual void DrawRect(float x, float y, float width, float height, float r, float g, float b, float a) = 0;
	virtual void BindTexture(class Texture* texture) = 0;

	virtual void UploadMesh(Vertex* data, int vertexCount) = 0;

	static GraphicsContext* Create(Window& window);
};

} // namespace Engine