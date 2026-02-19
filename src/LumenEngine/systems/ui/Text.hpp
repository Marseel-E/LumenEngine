#pragma once

#include <SDL_ttf.h>

#include <string>

#include "Element.hpp"
#include "LumenEngine/graphics/Texture.hpp"

namespace Engine::UI {

class Text : public Element {
public:
	Text(float x, float y, const std::string& text);
	virtual ~Text();

	void SetText(const std::string& text);

	void Render(GraphicsContext* context) override;

private:
	std::string m_text;
	Texture* m_textTexture = nullptr;

	void RebuildTexture();
};

} // namespace Engine::UI