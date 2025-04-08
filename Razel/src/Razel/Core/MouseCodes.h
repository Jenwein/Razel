#pragma once

namespace Razel
{
	typedef enum class MouseCode : uint16_t
	{
		// From glfw3.h
		Button0 = 0,
		Button1 = 1,
		Button2 = 2,
		Button3 = 3,
		Button4 = 4,
		Button5 = 5,
		Button6 = 6,
		Button7 = 7,

		ButtonLast = Button7,
		ButtonLeft = Button0,
		ButtonRight = Button1,
		ButtonMiddle = Button2
	} Mouse;

	inline std::ostream& operator<<(std::ostream& os, MouseCode mouseCode)
	{
		os << static_cast<int32_t>(mouseCode);
		return os;
	}
}

#define RZ_MOUSE_BUTTON_0      ::Razel::Mouse::Button0
#define RZ_MOUSE_BUTTON_1      ::Razel::Mouse::Button1
#define RZ_MOUSE_BUTTON_2      ::Razel::Mouse::Button2
#define RZ_MOUSE_BUTTON_3      ::Razel::Mouse::Button3
#define RZ_MOUSE_BUTTON_4      ::Razel::Mouse::Button4
#define RZ_MOUSE_BUTTON_5      ::Razel::Mouse::Button5
#define RZ_MOUSE_BUTTON_6      ::Razel::Mouse::Button6
#define RZ_MOUSE_BUTTON_7      ::Razel::Mouse::Button7
#define RZ_MOUSE_BUTTON_LAST   ::Razel::Mouse::ButtonLast
#define RZ_MOUSE_BUTTON_LEFT   ::Razel::Mouse::ButtonLeft
#define RZ_MOUSE_BUTTON_RIGHT  ::Razel::Mouse::ButtonRight
#define RZ_MOUSE_BUTTON_MIDDLE ::Razel::Mouse::ButtonMiddle