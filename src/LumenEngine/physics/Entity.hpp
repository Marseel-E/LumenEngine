#pragma once

#include "PhysicsObject.hpp"

namespace Engine {

class Entity : public PhysicsObject {
public:
	Entity(float x, float y, float w, float h, float r, float g, float b) : PhysicsObject(x, y, w, h, r, g, b) {};

	virtual ~Entity() = default;

	virtual void Update(float deltaTime) override { PhysicsObject::Update(deltaTime); };

	void TakeDamage(float amount) { m_health -= amount; };

	float GetHealth() const { return m_health; };

protected:
	float m_health = 100.0f;
	float m_maxHealth = 100.0f;
};

} // namespace Engine