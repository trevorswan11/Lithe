#pragma once

namespace Lithe {

	typedef enum class KeyCode : uint16_t
	{
		// From glfw3.h
		Space = 32,
		Apostrophe = 39, /* ' */
		Comma = 44, /* , */
		Minus = 45, /* - */
		Period = 46, /* . */
		Slash = 47, /* / */

		D0 = 48, /* 0 */
		D1 = 49, /* 1 */
		D2 = 50, /* 2 */
		D3 = 51, /* 3 */
		D4 = 52, /* 4 */
		D5 = 53, /* 5 */
		D6 = 54, /* 6 */
		D7 = 55, /* 7 */
		D8 = 56, /* 8 */
		D9 = 57, /* 9 */

		Semicolon = 59, /* ; */
		Equal = 61, /* = */

		A = 65,
		B = 66,
		C = 67,
		D = 68,
		E = 69,
		F = 70,
		G = 71,
		H = 72,
		I = 73,
		J = 74,
		K = 75,
		L = 76,
		M = 77,
		N = 78,
		O = 79,
		P = 80,
		Q = 81,
		R = 82,
		S = 83,
		T = 84,
		U = 85,
		V = 86,
		W = 87,
		X = 88,
		Y = 89,
		Z = 90,

		LeftBracket = 91,  /* [ */
		Backslash = 92,  /* \ */
		RightBracket = 93,  /* ] */
		GraveAccent = 96,  /* ` */

		World1 = 161, /* non-US #1 */
		World2 = 162, /* non-US #2 */

		/* Function keys */
		Escape = 256,
		Enter = 257,
		Tab = 258,
		Backspace = 259,
		Insert = 260,
		Delete = 261,
		Right = 262,
		Left = 263,
		Down = 264,
		Up = 265,
		PageUp = 266,
		PageDown = 267,
		Home = 268,
		End = 269,
		CapsLock = 280,
		ScrollLock = 281,
		NumLock = 282,
		PrintScreen = 283,
		Pause = 284,
		F1 = 290,
		F2 = 291,
		F3 = 292,
		F4 = 293,
		F5 = 294,
		F6 = 295,
		F7 = 296,
		F8 = 297,
		F9 = 298,
		F10 = 299,
		F11 = 300,
		F12 = 301,
		F13 = 302,
		F14 = 303,
		F15 = 304,
		F16 = 305,
		F17 = 306,
		F18 = 307,
		F19 = 308,
		F20 = 309,
		F21 = 310,
		F22 = 311,
		F23 = 312,
		F24 = 313,
		F25 = 314,

		/* Keypad */
		KP0 = 320,
		KP1 = 321,
		KP2 = 322,
		KP3 = 323,
		KP4 = 324,
		KP5 = 325,
		KP6 = 326,
		KP7 = 327,
		KP8 = 328,
		KP9 = 329,
		KPDecimal = 330,
		KPDivide = 331,
		KPMultiply = 332,
		KPSubtract = 333,
		KPAdd = 334,
		KPEnter = 335,
		KPEqual = 336,

		LeftShift = 340,
		LeftControl = 341,
		LeftAlt = 342,
		LeftSuper = 343,
		RightShift = 344,
		RightControl = 345,
		RightAlt = 346,
		RightSuper = 347,
		Menu = 348
	} Key;

	inline std::ostream& operator<<(std::ostream& os, KeyCode keyCode)
	{
		os << static_cast<int32_t>(keyCode);
		return os;
	}
}

// From glfw3.h
#define LI_KEY_SPACE           ::Lithe::Key::Space
#define LI_KEY_APOSTROPHE      ::Lithe::Key::Apostrophe    /* ' */
#define LI_KEY_COMMA           ::Lithe::Key::Comma         /* , */
/* Function keys */
#define LI_KEY_ESCAPE          ::Lithe::Key::Escape
#define LI_KEY_ENTER           ::Lithe::Key::Enter
#define LI_KEY_TAB             ::Lithe::Key::Tab
#define LI_KEY_BACKSPACE       ::Lithe::Key::Backspace
#define LI_KEY_INSERT          ::Lithe::Key::Insert
#define LI_KEY_DELETE          ::Lithe::Key::Delete
#define LI_KEY_RIGHT           ::Lithe::Key::Right
#define LI_KEY_LEFT            ::Lithe::Key::Left
#define LI_KEY_DOWN            ::Lithe::Key::Down
#define LI_KEY_UP              ::Lithe::Key::Up
#define LI_KEY_PAGE_UP         ::Lithe::Key::PageUp
#define LI_KEY_PAGE_DOWN       ::Lithe::Key::PageDown
#define LI_KEY_HOME            ::Lithe::Key::Home
#define LI_KEY_END             ::Lithe::Key::End
#define LI_KEY_CAPS_LOCK       ::Lithe::Key::CapsLock
#define LI_KEY_SCROLL_LOCK     ::Lithe::Key::ScrollLock
#define LI_KEY_NUM_LOCK        ::Lithe::Key::NumLock
#define LI_KEY_PRINT_SCREEN    ::Lithe::Key::PrintScreen
#define LI_KEY_PAUSE           ::Lithe::Key::Pause
#define LI_KEY_F1              ::Lithe::Key::F1
#define LI_KEY_F2              ::Lithe::Key::F2
#define LI_KEY_F3              ::Lithe::Key::F3
#define LI_KEY_F4              ::Lithe::Key::F4
#define LI_KEY_F5              ::Lithe::Key::F5
#define LI_KEY_F6              ::Lithe::Key::F6
#define LI_KEY_F7              ::Lithe::Key::F7
#define LI_KEY_F8              ::Lithe::Key::F8
#define LI_KEY_F9              ::Lithe::Key::F9
#define LI_KEY_F10             ::Lithe::Key::F10
#define LI_KEY_F11             ::Lithe::Key::F11
#define LI_KEY_F12             ::Lithe::Key::F12
#define LI_KEY_F13             ::Lithe::Key::F13
#define LI_KEY_F14             ::Lithe::Key::F14
#define LI_KEY_F15             ::Lithe::Key::F15
#define LI_KEY_F16             ::Lithe::Key::F16
#define LI_KEY_F17             ::Lithe::Key::F17
#define LI_KEY_F18             ::Lithe::Key::F18
#define LI_KEY_F19             ::Lithe::Key::F19
#define LI_KEY_F20             ::Lithe::Key::F20
#define LI_KEY_F21             ::Lithe::Key::F21
#define LI_KEY_F22             ::Lithe::Key::F22
#define LI_KEY_F23             ::Lithe::Key::F23
#define LI_KEY_F24             ::Lithe::Key::F24
#define LI_KEY_F25             ::Lithe::Key::F25

/* Keypad */
#define LI_KEY_KP_0            ::Lithe::Key::KP0
#define LI_KEY_KP_1            ::Lithe::Key::KP1
#define LI_KEY_KP_2            ::Lithe::Key::KP2
#define LI_KEY_KP_3            ::Lithe::Key::KP3
#define LI_KEY_KP_4            ::Lithe::Key::KP4
#define LI_KEY_KP_5            ::Lithe::Key::KP5
#define LI_KEY_KP_6            ::Lithe::Key::KP6
#define LI_KEY_KP_7            ::Lithe::Key::KP7
#define LI_KEY_KP_8            ::Lithe::Key::KP8
#define LI_KEY_KP_9            ::Lithe::Key::KP9
#define LI_KEY_KP_DECIMAL      ::Lithe::Key::KPDecimal
#define LI_KEY_KP_DIVIDE       ::Lithe::Key::KPDivide
#define LI_KEY_KP_MULTIPLY     ::Lithe::Key::KPMultiply
#define LI_KEY_KP_SUBTRACT     ::Lithe::Key::KPSubtract
#define LI_KEY_KP_ADD          ::Lithe::Key::KPAdd
#define LI_KEY_KP_ENTER        ::Lithe::Key::KPEnter
#define LI_KEY_KP_EQUAL        ::Lithe::Key::KPEqual

#define LI_KEY_LEFT_SHIFT      ::Lithe::Key::LeftShift
#define LI_KEY_LEFT_CONTROL    ::Lithe::Key::LeftControl
#define LI_KEY_LEFT_ALT        ::Lithe::Key::LeftAlt
#define LI_KEY_LEFT_SUPER      ::Lithe::Key::LeftSuper
#define LI_KEY_RIGHT_SHIFT     ::Lithe::Key::RightShift
#define LI_KEY_RIGHT_CONTROL   ::Lithe::Key::RightControl
#define LI_KEY_RIGHT_ALT       ::Lithe::Key::RightAlt
#define LI_KEY_RIGHT_SUPER     ::Lithe::Key::RightSuper
#define LI_KEY_MENU            ::Lithe::Key::Menu