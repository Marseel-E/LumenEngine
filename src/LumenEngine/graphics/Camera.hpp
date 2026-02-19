#pragma once

#include "LumenEngine/core/Math.hpp"

namespace Engine {

class Camera {
public:
	Camera(float width, float height);

	void SetPosition(const Vec2& position) {
		m_position = position;
		RecalculateView();
	};
	const Vec2& GetPosition() const { return m_position; };

	void SetProjection(float left, float right, float bottom, float top);

	const Mat4& GetViewProjectionMatrix() const { return m_viewProjectionMatrix; };

private:
	void RecalculateView();

	Mat4 m_projectionMatrix;
	Mat4 m_viewMatrix;
	Mat4 m_viewProjectionMatrix;

	Vec2 m_position = {0.0f, 0.0f};
	float m_rotation = 0.0f;
};

} // namespace Engine
