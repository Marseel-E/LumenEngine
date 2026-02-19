#pragma once

#include "Entity.hpp"
#include "LumenEngine/systems/Input.hpp"

namespace Engine {

class Player : public Entity {
public:
	Player(float x, float y) : Entity(x, y, 50.0f, 50.0f, 1.0f, 0.0f, 0.0f) {};

	void Update(float deltaTime) override {
		float speed = 400.0f;
		m_velocity.x = 0.0f;

		if (Input::IsKeyPressed(Key::D)) m_velocity.x = speed;
		if (Input::IsKeyPressed(Key::A)) m_velocity.x = -speed;

		if (Input::IsKeyPressed(Key::Space) && m_isGrounded) {
			m_velocity.y = -800.0f;
			m_isGrounded = false;
		};

		Entity::Update(deltaTime);
	};
};

} // namespace Engine