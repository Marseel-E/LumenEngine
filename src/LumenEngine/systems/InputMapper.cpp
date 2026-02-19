#include "InputMapper.hpp"

namespace Engine {

std::unordered_map<std::string, std::vector<Key>> InputMapper::m_actionMap;

void InputMapper::BindAction(const std::string& actionName, Key key) {
	m_actionMap[actionName].push_back(key);
};

bool InputMapper::IsActionPressed(const std::string& actionName) {
	auto it = m_actionMap.find(actionName);

	if (it == m_actionMap.end()) return false;

	for (Key key : it->second) {
		if (Input::IsKeyPressed(key)) {
			return true;
		};
	};

	return false;
};

void InputMapper::Clear() {
	m_actionMap.clear();
};

} // namespace Engine