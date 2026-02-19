#pragma once

#include "Object.hpp"

namespace Engine {

class StaticObject : public Object {
public:
	StaticObject(float x, float y, float w, float h, float r, float g, float b) : Object(x, y, w, h, r, g, b) {};
};

} // namespace Engine