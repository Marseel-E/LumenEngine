#pragma once

#include <cmath>
#include <cstring>

namespace Engine {

struct Vec2 {
	float x, y;
};
struct Vec3 {
	float x, y, z;
};
struct Vec4 {
	float x, y, z, w;
};

struct Rect {
	float x, y;
	float width, height;

	bool Intersects(const Rect& other) const {
		return (x < other.x + other.width && x + width > other.x && y < other.y + other.height && y + height > other.y);
	};
};

struct alignas(16) Mat4 {
	float m[4][4];

	static Mat4 Identity() {
		Mat4 res = {};

		std::memset(res.m, 0, sizeof(res.m));

		for (int i = 0; i < 4; i++) res.m[i][i] = 1.0f;

		return res;
	};

	static Mat4 Translate(const Vec3& v) {
		Mat4 res = Identity();

		res.m[3][0] = v.x;
		res.m[3][1] = v.y;
		res.m[3][2] = v.z;

		return res;
	};

	static Mat4 Multiply(const Mat4& A, const Mat4& B) {
		Mat4 res;

		for (int c = 0; c < 4; c++) {
			for (int r = 0; r < 4; r++) {
				res.m[c][r] = 0.0f;

				for (int k = 0; k < 4; k++) {
					res.m[c][r] += A.m[k][r] * B.m[c][k];
				};
			};
		};

		return res;
	};

	static Mat4 Orthographic(float left, float right, float bottom, float top, float near, float far) {
		Mat4 res = Identity();

		res.m[0][0] = 2.0f / (right - left);
		res.m[1][1] = 2.0f / (top - bottom);
		res.m[2][2] = 1.0f / (far - near);
		res.m[3][0] = -(right + left) / (right - left);
		res.m[3][1] = -(top + bottom) / (top - bottom);
		res.m[3][2] = -near / (far - near);

		return res;
	};
};

} // namespace Engine