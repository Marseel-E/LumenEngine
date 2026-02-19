#include "Renderer.hpp"

namespace Engine {

Renderer::Renderer(GraphicsContext* context) : m_context(context) {};

void Renderer::BeginScene(Camera& camera) {
	m_context->SetCamera(camera.GetViewProjectionMatrix());
};

void Renderer::EndScene() {};

void Renderer::DrawRect(float x, float y, float w, float h, float r, float g, float b, float a) {
	m_context->DrawRect(x, y, w, h, r, g, b, a);
};

void Renderer::DrawEntity(Entity* entity) {
	Rect r = entity->GetBounds();
	Vec4 c = entity->GetColor();
	m_context->DrawRect(r.x, r.y, r.width, r.height, c.x, c.y, c.z, c.w);
};

void Renderer::DrawStaticObject(StaticObject* obj) {
	Rect r = obj->GetBounds();
	Vec4 c = obj->GetColor();
	m_context->DrawRect(r.x + 1, r.y + 1, r.width - 2, r.height - 2, c.x, c.y, c.z, c.w);
};

} // namespace Engine