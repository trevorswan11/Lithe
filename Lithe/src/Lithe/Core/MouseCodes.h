#pragma once

namespace Lithe {

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

#define LI_MOUSE_BUTTON_0      ::Lithe::Mouse::Button0
#define LI_MOUSE_BUTTON_1      ::Lithe::Mouse::Button1
#define LI_MOUSE_BUTTON_2      ::Lithe::Mouse::Button2
#define LI_MOUSE_BUTTON_3      ::Lithe::Mouse::Button3
#define LI_MOUSE_BUTTON_4      ::Lithe::Mouse::Button4
#define LI_MOUSE_BUTTON_5      ::Lithe::Mouse::Button5
#define LI_MOUSE_BUTTON_6      ::Lithe::Mouse::Button6
#define LI_MOUSE_BUTTON_7      ::Lithe::Mouse::Button7
#define LI_MOUSE_BUTTON_LAST   ::Lithe::Mouse::ButtonLast
#define LI_MOUSE_BUTTON_LEFT   ::Lithe::Mouse::ButtonLeft
#define LI_MOUSE_BUTTON_RIGHT  ::Lithe::Mouse::ButtonRight
#define LI_MOUSE_BUTTON_MIDDLE ::Lithe::Mouse::ButtonMiddle