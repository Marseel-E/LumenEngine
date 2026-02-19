#include "Input.hpp"

namespace Engine {

std::unordered_map<int, bool> Input::m_keys;

bool Input::IsKeyPressed(Key keycode) {
	return m_keys[static_cast<int>(keycode)];
};

void Input::SetKey(int keycode, bool state) {
	m_keys[keycode] = state;
};

void Input::SetMouseButton(int button, bool state) {
	if (button == 1) m_keys[static_cast<int>(Key::MouseLeftClick)] = state;
	if (button == 3) m_keys[static_cast<int>(Key::MouseRightClick)] = state;
	if (button == 2) m_keys[static_cast<int>(Key::MouseMiddleClick)] = state;
};

} // namespace Engine