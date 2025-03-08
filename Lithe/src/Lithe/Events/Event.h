#pragma once

#include "Lithe/Core/Base.h"

namespace Lithe {

	// Specifies the exact type of the event, which can be:
	// - None
	// - Window Events: WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
	// - App Events: AppTick, AppUpdate, AppRender,
	// - Key Events: KeyPressed, KeyReleased, KeyTyped
	// - Mouse Events: MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
	// All of which have their own specific implementations/uses
	enum class EventType
	{
		None = 0,
		WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
		AppTick, AppUpdate, AppRender,
		KeyPressed, KeyReleased, KeyTyped,
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
	};

	// Provides a filter for different events -- acts as a trait; An event can fall into more than one category:
	// - None
	// - EventCategoryApplication
	// - EventCategoryInput
	// - EventCategoryKeyboard
	// - EventCategoryMouse
	// - EventCategoryMouseButton
	// These are used as qualifiers for the EVENT_CLASS_CATEGORY macro
	enum EventCategory
	{
		None = 0,
		EventCategoryApplication =	BIT(0),
		EventCategoryInput =		BIT(1),
		EventCategoryKeyboard =		BIT(2),
		EventCategoryMouse =		BIT(3),
		EventCategoryMouseButton =	BIT(4)
	};

// Macro to initialize usefl getter methods while reducing bloat and code duplication
#define EVENT_CLASS_TYPE(type) static EventType GetStaticType() { return EventType::##type; }\
								virtual EventType GetEventType() const override { return GetStaticType(); }\
								virtual const char* GetName() const override { return #type; }

// Doesn't necessarily need to be a macro, but acts as a common declaration for implementation behavior
#define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const override { return category; }

	// Base class for any event, defining shared behavior and implementation
	class LITHE_API Event
	{
		friend class EventDispatcher;
	public:
		bool Handled = false;
		// Pure virtual functions, like GetEventType, GetName, and GetCategoryFlags MUST be implemented

		virtual EventType GetEventType() const = 0;
		virtual const char* GetName() const = 0;
		virtual int GetCategoryFlags() const = 0;
		// ToString is going to be purely debug, performance will not be considered

		virtual std::string ToString() const { return GetName(); } // Can override to print special information

		// Determines if an event is part of a given category, but does not guarantee ownership by a single category
		inline bool IsInCategory(EventCategory category)
		{
			return GetCategoryFlags() & category;
		}
	};

	// Dispatches any received event through the application
	class EventDispatcher
	{
	public:
		EventDispatcher(Event& event)
			: m_Event(event) {}

		// Dispatches any event using a specified function 
		template<typename T, typename F>
		bool Dispatch(const F& func)
		{
			// Check the inputted event aginst the template type (template types declared as <Type>)
			if (m_Event.GetEventType() == T::GetStaticType())
			{
				m_Event.Handled = func(*(T*)&m_Event);
				return true;
			}
			return false;
		}
	private:
		Event& m_Event;
	};

	// Assists in correct logging of events
	inline std::string format_as(const Event& e)
	{
		return e.ToString();
	}

	inline std::ostream& operator<<(std::ostream& os, const Event& e)
	{
		return os << e.ToString();
	}

}