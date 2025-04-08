#pragma once

namespace Razel
{
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
#define RZ_KEY_SPACE           ::Razel::Key::Space
#define RZ_KEY_APOSTROPHE      ::Razel::Key::Apostrophe    /* ' */
#define RZ_KEY_COMMA           ::Razel::Key::Comma         /* , */
#define RZ_KEY_MINUS           ::Razel::Key::Minus         /* - */
#define RZ_KEY_PERIOD          ::Razel::Key::Period        /* . */
#define RZ_KEY_SLASH           ::Razel::Key::Slash         /* / */
#define RZ_KEY_0               ::Razel::Key::D0
#define RZ_KEY_1               ::Razel::Key::D1
#define RZ_KEY_2               ::Razel::Key::D2
#define RZ_KEY_3               ::Razel::Key::D3
#define RZ_KEY_4               ::Razel::Key::D4
#define RZ_KEY_5               ::Razel::Key::D5
#define RZ_KEY_6               ::Razel::Key::D6
#define RZ_KEY_7               ::Razel::Key::D7
#define RZ_KEY_8               ::Razel::Key::D8
#define RZ_KEY_9               ::Razel::Key::D9
#define RZ_KEY_SEMICOLON       ::Razel::Key::Semicolon     /* ; */
#define RZ_KEY_EQUAL           ::Razel::Key::Equal         /* = */
#define RZ_KEY_A               ::Razel::Key::A
#define RZ_KEY_B               ::Razel::Key::B
#define RZ_KEY_C               ::Razel::Key::C
#define RZ_KEY_D               ::Razel::Key::D
#define RZ_KEY_E               ::Razel::Key::E
#define RZ_KEY_F               ::Razel::Key::F
#define RZ_KEY_G               ::Razel::Key::G
#define RZ_KEY_H               ::Razel::Key::H
#define RZ_KEY_I               ::Razel::Key::I
#define RZ_KEY_J               ::Razel::Key::J
#define RZ_KEY_K               ::Razel::Key::K
#define RZ_KEY_L               ::Razel::Key::L
#define RZ_KEY_M               ::Razel::Key::M
#define RZ_KEY_N               ::Razel::Key::N
#define RZ_KEY_O               ::Razel::Key::O
#define RZ_KEY_P               ::Razel::Key::P
#define RZ_KEY_Q               ::Razel::Key::Q
#define RZ_KEY_R               ::Razel::Key::R
#define RZ_KEY_S               ::Razel::Key::S
#define RZ_KEY_T               ::Razel::Key::T
#define RZ_KEY_U               ::Razel::Key::U
#define RZ_KEY_V               ::Razel::Key::V
#define RZ_KEY_W               ::Razel::Key::W
#define RZ_KEY_X               ::Razel::Key::X
#define RZ_KEY_Y               ::Razel::Key::Y
#define RZ_KEY_Z               ::Razel::Key::Z
#define RZ_KEY_LEFT_BRACKET    ::Razel::Key::LeftBracket   /* [ */
#define RZ_KEY_BACKSLASH       ::Razel::Key::Backslash     /* \ */
#define RZ_KEY_RIGHT_BRACKET   ::Razel::Key::RightBracket  /* ] */
#define RZ_KEY_GRAVE_ACCENT    ::Razel::Key::GraveAccent   /* ` */
#define RZ_KEY_WORLD_1         ::Razel::Key::World1        /* non-US #1 */
#define RZ_KEY_WORLD_2         ::Razel::Key::World2        /* non-US #2 */

/* Function keys */
#define RZ_KEY_ESCAPE          ::Razel::Key::Escape
#define RZ_KEY_ENTER           ::Razel::Key::Enter
#define RZ_KEY_TAB             ::Razel::Key::Tab
#define RZ_KEY_BACKSPACE       ::Razel::Key::Backspace
#define RZ_KEY_INSERT          ::Razel::Key::Insert
#define RZ_KEY_DELETE          ::Razel::Key::Delete
#define RZ_KEY_RIGHT           ::Razel::Key::Right
#define RZ_KEY_LEFT            ::Razel::Key::Left
#define RZ_KEY_DOWN            ::Razel::Key::Down
#define RZ_KEY_UP              ::Razel::Key::Up
#define RZ_KEY_PAGE_UP         ::Razel::Key::PageUp
#define RZ_KEY_PAGE_DOWN       ::Razel::Key::PageDown
#define RZ_KEY_HOME            ::Razel::Key::Home
#define RZ_KEY_END             ::Razel::Key::End
#define RZ_KEY_CAPS_LOCK       ::Razel::Key::CapsLock
#define RZ_KEY_SCROLL_LOCK     ::Razel::Key::ScrollLock
#define RZ_KEY_NUM_LOCK        ::Razel::Key::NumLock
#define RZ_KEY_PRINT_SCREEN    ::Razel::Key::PrintScreen
#define RZ_KEY_PAUSE           ::Razel::Key::Pause
#define RZ_KEY_F1              ::Razel::Key::F1
#define RZ_KEY_F2              ::Razel::Key::F2
#define RZ_KEY_F3              ::Razel::Key::F3
#define RZ_KEY_F4              ::Razel::Key::F4
#define RZ_KEY_F5              ::Razel::Key::F5
#define RZ_KEY_F6              ::Razel::Key::F6
#define RZ_KEY_F7              ::Razel::Key::F7
#define RZ_KEY_F8              ::Razel::Key::F8
#define RZ_KEY_F9              ::Razel::Key::F9
#define RZ_KEY_F10             ::Razel::Key::F10
#define RZ_KEY_F11             ::Razel::Key::F11
#define RZ_KEY_F12             ::Razel::Key::F12
#define RZ_KEY_F13             ::Razel::Key::F13
#define RZ_KEY_F14             ::Razel::Key::F14
#define RZ_KEY_F15             ::Razel::Key::F15
#define RZ_KEY_F16             ::Razel::Key::F16
#define RZ_KEY_F17             ::Razel::Key::F17
#define RZ_KEY_F18             ::Razel::Key::F18
#define RZ_KEY_F19             ::Razel::Key::F19
#define RZ_KEY_F20             ::Razel::Key::F20
#define RZ_KEY_F21             ::Razel::Key::F21
#define RZ_KEY_F22             ::Razel::Key::F22
#define RZ_KEY_F23             ::Razel::Key::F23
#define RZ_KEY_F24             ::Razel::Key::F24
#define RZ_KEY_F25             ::Razel::Key::F25

/* Keypad */
#define RZ_KEY_KP_0            ::Razel::Key::KP0
#define RZ_KEY_KP_1            ::Razel::Key::KP1
#define RZ_KEY_KP_2            ::Razel::Key::KP2
#define RZ_KEY_KP_3            ::Razel::Key::KP3
#define RZ_KEY_KP_4            ::Razel::Key::KP4
#define RZ_KEY_KP_5            ::Razel::Key::KP5
#define RZ_KEY_KP_6            ::Razel::Key::KP6
#define RZ_KEY_KP_7            ::Razel::Key::KP7
#define RZ_KEY_KP_8            ::Razel::Key::KP8
#define RZ_KEY_KP_9            ::Razel::Key::KP9
#define RZ_KEY_KP_DECIMAL      ::Razel::Key::KPDecimal
#define RZ_KEY_KP_DIVIDE       ::Razel::Key::KPDivide
#define RZ_KEY_KP_MULTIPLY     ::Razel::Key::KPMultiply
#define RZ_KEY_KP_SUBTRACT     ::Razel::Key::KPSubtract
#define RZ_KEY_KP_ADD          ::Razel::Key::KPAdd
#define RZ_KEY_KP_ENTER        ::Razel::Key::KPEnter
#define RZ_KEY_KP_EQUAL        ::Razel::Key::KPEqual

#define RZ_KEY_LEFT_SHIFT      ::Razel::Key::LeftShift
#define RZ_KEY_LEFT_CONTROL    ::Razel::Key::LeftControl
#define RZ_KEY_LEFT_ALT        ::Razel::Key::LeftAlt
#define RZ_KEY_LEFT_SUPER      ::Razel::Key::LeftSuper
#define RZ_KEY_RIGHT_SHIFT     ::Razel::Key::RightShift
#define RZ_KEY_RIGHT_CONTROL   ::Razel::Key::RightControl
#define RZ_KEY_RIGHT_ALT       ::Razel::Key::RightAlt
#define RZ_KEY_RIGHT_SUPER     ::Razel::Key::RightSuper
#define RZ_KEY_MENU            ::Razel::Key::Menu