#pragma once

#include <vector>

#include "Element.hpp"

namespace Engine::UI {

class Screen {
public:
	~Screen() {
		for (auto* e : m_elements) delete e;

		m_elements.clear();
	};

	void AddElement(Element* element) { m_elements.push_back(element); };

	void Update(float deltaTime) {
		if (!m_visible) return;

		for (auto* e : m_elements) {
			if (e->IsActive()) e->Update(deltaTime);
		};
	};

	void Render(GraphicsContext* context) {
		if (!m_visible) return;

		for (auto* e : m_elements) {
			if (e->IsActive()) e->Render(context);
		};
	};

	void SetVisible(bool visible) { m_visible = visible; };
	bool IsVisible() const { return m_visible; };

private:
	std::vector<Element*> m_elements;
	bool m_visible = true;
};

} // namespace Engine::UI