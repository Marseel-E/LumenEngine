#pragma once

#include <vector>

#include "PhysicsObject.hpp"
#include "StaticObject.hpp"

namespace Engine {

class PhysicsEngine {
public:
	void AddObject(PhysicsObject* obj) { m_moveableObjects.push_back(obj); };
	void AddObject(StaticObject* obj) { m_staticObjects.push_back(obj); };

	void Update(float deltaTime);

private:
	std::vector<PhysicsObject*> m_moveableObjects;
	std::vector<StaticObject*> m_staticObjects;

	void CheckCollisions(PhysicsObject* obj);
};

} // namespace Engine