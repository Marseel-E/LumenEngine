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

		if (std::abs(playerRect.x - blockRect.x) > 100.0f || std::abs(playerRect.y - blockRect.y) > 100.0f) {
			continue;
		};

		if (playerRect.Intersects(blockRect)) {
			float pCenterX = playerRect.x + (playerRect.width / 2.0f);
			float pCenterY = playerRect.y + (playerRect.height / 2.0f);

			float bCenterX = blockRect.x + (blockRect.width / 2.0f);
			float bCenterY = blockRect.y + (blockRect.height / 2.0f);

			float pHalfW = playerRect.width / 2.0f;
			float pHalfH = playerRect.height / 2.0f;

			float bHalfW = blockRect.width / 2.0f;
			float bHalfH = blockRect.height / 2.0f;

			float diffX = pCenterX - bCenterX;
			float diffY = pCenterY - bCenterY;

			float overlapX = (pHalfW + bHalfW) - std::abs(diffX);
			float overlapY = (pHalfH + bHalfH) - std::abs(diffY);

			if (overlapX < overlapY) {
				Vec2 pos = obj->GetPosition();
				Vec2 vel = obj->GetVelocity();

				if (diffX > 0)
					pos.x += overlapX;
				else
					pos.x -= overlapX;

				vel.x = 0;
				obj->SetPosition(pos);
				obj->SetVelocity(vel);
			} else {
				Vec2 pos = obj->GetPosition();
				Vec2 vel = obj->GetVelocity();

				if (vel.y >= 0) {
					pos.y -= overlapY;
					onGround = true;
				} else {
					pos.y += overlapY;
				}

				vel.y = 0;
				obj->SetPosition(pos);
				obj->SetVelocity(vel);
			}

			playerRect = obj->GetBounds();
		};
	};

	obj->SetGrounded(onGround);
};

} // namespace Engine