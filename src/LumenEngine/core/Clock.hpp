#pragma once

#include <SDL2/SDL.h>

namespace Engine {

class Clock {
public:
	Clock() {
		m_lastTime = SDL_GetPerformanceCounter();
		m_deltaTime = 0.0f;
	};

	void Tick() {
		Uint64 now = SDL_GetPerformanceCounter();

		m_deltaTime = (float)(now - m_lastTime) / (float)SDL_GetPerformanceFrequency();

		m_lastTime = now;
	};

	float GetDeltaTime() const { return m_deltaTime; };

private:
	Uint64 m_lastTime;
	float m_deltaTime;
};

} // namespace Engine