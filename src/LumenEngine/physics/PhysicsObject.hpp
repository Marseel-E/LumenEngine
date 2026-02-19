#pragma once

#include "Object.hpp"

namespace Engine {

class PhysicsObject : public Object {
public:
	PhysicsObject(float x, float y, float w, float h, float r, float g, float b) : Object(x, y, w, h, r, g, b) {};

	virtual void Update(float deltaTime) {
		m_velocity.y += m_gravity * deltaTime;

		m_position.x += m_velocity.x * deltaTime;
		m_position.y += m_velocity.y * deltaTime;
	};

	void AddForce(Vec2 force) {
		m_velocity.x += force.x;
		m_velocity.y += force.y;
	};

	Vec2 GetVelocity() const { return m_velocity; };
	void SetVelocity(Vec2 v) { m_velocity = v; };

	bool IsGrounded() const { return m_isGrounded; };
	void SetGrounded(bool state) { m_isGrounded = state; };

protected:
	Vec2 m_velocity = {0.0f, 0.0f};
	float m_gravity = 2000.0f;
	bool m_isGrounded = false;
};

} // namespace Engine