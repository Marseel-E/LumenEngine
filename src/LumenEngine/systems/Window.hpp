#pragma once

#include <string>

struct SDL_Window;

namespace Engine {

class Window {
public:
	Window(int width, int height, const std::string& title);
	~Window();

	bool Init();
	void Shutdown();

	bool PollEvents();

	void* GetNativeWindow() const { return m_window; }
	int GetWidth() const { return m_width; }
	int GetHeight() const { return m_height; }

private:
	int m_width;
	int m_height;

	std::string m_title;

	SDL_Window* m_window;
};

} // namespace Engine