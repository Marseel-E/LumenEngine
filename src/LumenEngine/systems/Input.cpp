#include "Input.hpp"

namespace Engine {

std::unordered_map<int, bool> Input::m_keys;

bool Input::IsKeyPressed(Key keycode) {
	return m_keys[static_cast<int>(keycode)];
};

void Input::SetKey(int keycode, bool state) {
	m_keys[keycode] = state;
};

} // namespace Engine