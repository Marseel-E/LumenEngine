#pragma once

#include <string>
#include <unordered_map>

#include "LumenEngine/graphics/Camera.hpp"
#include "Screen.hpp"

namespace Engine::UI {

class Manager {
public:
	Manager(float width, float height) : m_uiCamera(width, height) { m_uiCamera.SetPosition({0.0f, 0.0f}); };

	~Manager() {
		for (auto& pair : m_screens) delete pair.second;
		m_screens.clear();
	};

	Screen* CreateScreen(const std::string& name) {
		Screen* screen = new Screen();
		m_screens[name] = screen;

		return screen;
	};

	Screen* GetScreen(const std::string& name) { return m_screens[name]; };

	void Update(float deltaTime) {
		for (auto& pair : m_screens) {
			pair.second->Update(deltaTime);
		};
	};

	void Render(GraphicsContext* context) {
		context->SetCamera(m_uiCamera.GetViewProjectionMatrix());

		for (auto& pair : m_screens) {
			pair.second->Render(context);
		};
	};

private:
	std::unordered_map<std::string, Screen*> m_screens;
	Camera m_uiCamera;
};

} // namespace Engine::UI