#pragma once

#include "Event.h"

// OS will take a key pressed event, and then if the key is still 
// pressed then it will repeat the key event until key released is called

namespace Lithe {
	class LITHE_API KeyEvent : public Event
	{
	public:
		inline int GetKeyCode() const { return m_KeyCode; }
		// Any keyboard event is also an input event, so or them together

		EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)
	protected:
		// Should not be able to make this class (technically an abstract class)

		KeyEvent(int keycode) : m_KeyCode(keycode) {}
		int m_KeyCode;
	};

	class LITHE_API KeyPressedEvent : public KeyEvent
	{
	public:
		KeyPressedEvent(int keycode, int repeatCount)
			: KeyEvent(keycode), m_RepeatCount(repeatCount) {}

		inline int GetRepeatCount() const { return m_RepeatCount; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyPressedEvent: " << m_KeyCode << " (" << m_RepeatCount << " repeats)";
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyPressed)
	private:
		int m_RepeatCount;
	};

	class LITHE_API KeyReleasedEvent : public KeyEvent
	{
	public:
		KeyReleasedEvent(int keycode)
			: KeyEvent(keycode) {}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyReleasedEvent: " << m_KeyCode;
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyPressed)
	};
}