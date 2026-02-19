#pragma once

#include "LumenEngine/core/Math.hpp"
#include "LumenEngine/graphics/GraphicsContext.hpp"

namespace Engine {

class Object {
public:
	Object(float x, float y, float w, float h, float r, float g, float b)
		: m_position({x, y}), m_size({w, h}), m_color({r, g, b, 1.0f}) {};

	virtual ~Object() = default;

	virtual void Render(GraphicsContext* context) {
		context->DrawRect(m_position.x, m_position.y, m_size.x, m_size.y, m_color.x, m_color.y, m_color.z, m_color.w);
	};

	Vec2 GetPosition() const { return m_position; };
	void SetPosition(const Vec2& pos) { m_position = pos; };

	Rect GetBounds() const { return {m_position.x, m_position.y, m_size.x, m_size.y}; };

protected:
	Vec2 m_position;
	Vec2 m_size;
	Vec4 m_color;
};

} // namespace Engine