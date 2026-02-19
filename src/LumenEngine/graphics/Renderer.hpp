#pragma once

#include "Camera.hpp"
#include "GraphicsContext.hpp"
#include "LumenEngine/physics/Entity.hpp"
#include "LumenEngine/physics/StaticObject.hpp"

namespace Engine {

class Renderer {
public:
	Renderer(GraphicsContext* context);
	~Renderer() = default;

	void BeginScene(Camera& camera);
	void EndScene();

	void DrawRect(float x, float y, float w, float h, float r, float g, float b, float a = 1.0f);

	void DrawEntity(Entity* entity);
	void DrawStaticObject(StaticObject* obj);

private:
	GraphicsContext* m_context;
};

} // namespace Engine