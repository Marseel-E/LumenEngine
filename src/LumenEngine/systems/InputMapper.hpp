#pragma once

#include <string>
#include <unordered_map>
#include <vector>

#include "Input.hpp"

namespace Engine {
class InputMapper {
public:
	static void BindAction(const std::string& actionName, Key key);

	static bool IsActionPressed(const std::string& actionName);

	static void Clear();

private:
	static std::unordered_map<std::string, std::vector<Key>> m_actionMap;
};
} // namespace Engine