#include "Camera.hpp"

namespace Engine {

Camera::Camera(float width, float height) {
	m_projectionMatrix = Mat4::Orthographic(0.0f, width, height, 0.0f, -1.0f, 1.0f);
	m_viewMatrix = Mat4::Identity();
	m_viewProjectionMatrix = m_projectionMatrix;
};

void Camera::SetProjection(float left, float right, float bottom, float top) {
	m_projectionMatrix = Mat4::Orthographic(left, right, bottom, top, -1.0f, 1.0f);

	RecalculateView();
};

void Camera::RecalculateView() {
	m_viewMatrix = Mat4::Translate({-m_position.x, -m_position.y, 0.0f});

	m_viewProjectionMatrix = Mat4::Multiply(m_projectionMatrix, m_viewMatrix);
};

} // namespace Engine