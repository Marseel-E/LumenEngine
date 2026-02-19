#include "Window.hpp"

#include <SDL2/SDL.h>
#include <SDL2/SDL_syswm.h>
#include <SDL_ttf.h>

#include "Input.hpp"
#include "LumenEngine/core/Logger.hpp"

namespace Engine {

Window::Window(int width, int height, const std::string& title)
	: m_width(width), m_height(height), m_title(title), m_window(nullptr) {};

Window::~Window() {
	Shutdown();
};

bool Window::Init() {
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		Logger::Error("SDL Init Error");

		return false;
	};

	if (TTF_Init() == -1) {
		Logger::Error("SDL_ttf could not initialize", TTF_GetError());

		return false;
	};

	m_window = SDL_CreateWindow(m_title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, m_width, m_height,
								SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);

	if (!m_window) {
		Logger::Error("Window Creation Error", SDL_GetError());

		return false;
	};

	return true;
};

void Window::Shutdown() {
	if (m_window) {
		SDL_DestroyWindow(m_window);

		m_window = nullptr;
	};

	SDL_Quit();
};

bool Window::PollEvents() {
	SDL_Event event;

	while (SDL_PollEvent(&event)) {
		// Window closed.
		if (event.type == SDL_QUIT) {
			return false;
		}

		// Input handling
		else if (event.type == SDL_KEYDOWN) {
			Input::SetKey(event.key.keysym.sym, true);
		}

		else if (event.type == SDL_KEYUP) {
			Input::SetKey(event.key.keysym.sym, false);
		};
	};

	return true;
};

} // namespace Engine