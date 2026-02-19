#pragma once

#include "Text.hpp"

namespace Engine::UI {

class Counter : public Text {
public:
	Counter(float x, float y, const std::string& prefix = "") : Text(x, y, "0"), m_prefix(prefix) {};

	void SetValue(int value) { SetText(m_prefix + std::to_string(value)); };

private:
	std::string m_prefix;
};

} // namespace Engine::UI