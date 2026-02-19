#pragma once

#include <unordered_map>

namespace Engine {

enum class Key {
	// Letters
	A = 97,
	B = 98,
	C = 99,
	D = 100,
	E = 101,
	F = 102,
	G = 103,
	H = 104,
	I = 105,
	J = 106,
	K = 107,
	L = 108,
	M = 109,
	N = 110,
	O = 111,
	P = 112,
	Q = 113,
	R = 114,
	S = 115,
	T = 116,
	U = 117,
	V = 118,
	W = 119,
	X = 120,
	Y = 121,
	Z = 122,

	// Numbers
	D0 = 48,
	D1 = 49,
	D2 = 50,
	D3 = 51,
	D4 = 52,
	D5 = 53,
	D6 = 54,
	D7 = 55,
	D8 = 56,
	D9 = 57,

	// Controls
	Space = 32,
	Escape = 27,
	Enter = 13,
	Backspace = 8,
	Tab = 9,

	// Arrows
	Right = 1073741903,
	Left = 1073741904,
	Down = 1073741905,
	Up = 1073741906,

	// Function Keys
	F1 = 1073741882,
	F2 = 1073741883,
	F3 = 1073741884,
	F4 = 1073741885,
	F5 = 1073741886,
	F6 = 1073741887,
	F7 = 1073741888,
	F8 = 1073741889,
	F9 = 1073741890,
	F10 = 1073741891,
	F11 = 1073741892,
	F12 = 1073741893,

	// Mouse
	MouseLeftClick = 1001,
	MouseRightClick = 1002,
	MouseMiddleClick = 1003,

	// Symbols
	ForwardSlash = 47,
	BackSlash = 92,
	Comma = 44,
	Period = 46
};

class Input {
public:
	static bool IsKeyPressed(Key keycode);

	static void SetKey(int keycode, bool state);

	static void SetMouseButton(int button, bool state);

private:
	static std::unordered_map<int, bool> m_keys;
};

} // namespace Engine