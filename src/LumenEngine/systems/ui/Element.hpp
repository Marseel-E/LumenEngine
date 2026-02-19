#pragma once

#include "LumenEngine/core/Math.hpp"
#include "LumenEngine/graphics/GraphicsContext.hpp"

namespace Engine::UI {

class Element {
public:
	Element(float x, float y) : m_position({x, y}) {};
	virtual ~Element() = default;

	virtual void Update(float deltaTime) {};
	virtual void Render(GraphicsContext* context) = 0;

	void SetActive(bool active) { m_active = active; };
	bool IsActive() const { return m_active; };

	void SetPosition(float x, float y) { m_position = {x, y}; };
	Vec2 GetPosition() const { return m_position; };

protected:
	Vec2 m_position;
	bool m_active = true;
};

} // namespace Engine::UI