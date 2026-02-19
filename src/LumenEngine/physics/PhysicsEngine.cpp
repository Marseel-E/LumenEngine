#include "PhysicsEngine.hpp"

#include <cmath>

namespace Engine {

void PhysicsEngine::Update(float deltaTime) {
	for (PhysicsObject* obj : m_moveableObjects) {
		obj->Update(deltaTime);

		CheckCollisions(obj);
	};
};

void PhysicsEngine::CheckCollisions(PhysicsObject* obj) {
	Rect playerRect = obj->GetBounds();
	bool onGround = false;

	for (StaticObject* block : m_staticObjects) {
		Rect blockRect = block->GetBounds();

		if (playerRect.Intersects(blockRect)) {
			if (obj->GetVelocity().y > 0) {
				Vec2 pos = obj->GetPosition();
				pos.y = blockRect.y - playerRect.height;
				obj->SetPosition(pos);

				Vec2 vel = obj->GetVelocity();
				vel.y = 0;
				obj->SetVelocity(vel);

				onGround = true;
			};
		};
	};

	obj->SetGrounded(onGround);
};

} // namespace Engine