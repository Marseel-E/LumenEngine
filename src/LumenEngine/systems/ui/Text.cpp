#include "Text.hpp"

#include "LumenEngine/core/Logger.hpp"
#include "LumenEngine/graphics/GraphicsContext.hpp"

namespace Engine::UI {

Text::Text(float x, float y, const std::string& text) : Element(x, y), m_text(text) {
	RebuildTexture();
};

Text::~Text() {
	if (m_textTexture) {
		delete m_textTexture;
		m_textTexture = nullptr;
	};
};

void Text::SetText(const std::string& text) {
	if (m_text == text) return;

	m_text = text;

	RebuildTexture();
};

void Text::Render(GraphicsContext* context) {
	if (m_textTexture) {
		float drawW = (float)m_textTexture->GetWidth();
		float drawH = (float)m_textTexture->GetHeight();

		m_textTexture->Render(context, m_position.x, m_position.y, drawW, drawH);
	};
};

void Text::RebuildTexture() {
	if (m_textTexture) {
		delete m_textTexture;
		m_textTexture = nullptr;
	};

	static TTF_Font* font = TTF_OpenFont("assets/fonts/Roboto-Regular.ttf", 24);
	if (!font) {
		Logger::Error("Failed to load font", std::string(TTF_GetError()));

		return;
	};

	SDL_Color color = {0, 255, 255, 255}; // Yellow (CMYK?)
	SDL_Surface* surface = TTF_RenderText_Blended(font, m_text.c_str(), color);

	if (surface) {
		m_textTexture = new Texture(surface->pixels, surface->w, surface->h, surface->pitch);

		SDL_FreeSurface(surface);
	};
};

} // namespace Engine::UI