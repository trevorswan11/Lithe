#pragma once

#include "Lithe/Core.h"

#include <string>
#include <functional>

namespace Lithe {
	enum class EventType
	{
		None = 0,
		WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
		AppTick, AppUpdate, AppRender,
		KeyPressed, KeyReleased,
		MouseBUttonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
	};

	// Provides a filter for different events -- acts as a trait
	enum EventCategory
	{
		None = 0,
		EventCategoryApplication =	BIT(0),
		EventCategoryInput =		BIT(1),
		EventCategoryKeyboard =		BIT(2),
		EventCategoryMouse =		BIT(3),
		EventCategoryMouseButton =	BIT(4)
	};

#define EVENT_CLASS_TYPE(type) static EventType GetStaticType() { return EventType::##type; }\
								virtual EventType GetEventType() const override { return GetStaticType(); }\
								virtual const char* GetName() const override { return #type; }

#define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const override { return category; }

	class LITHE_API Event
	{
		friend class EventDispatcher;
	public:
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
	protected:
		bool m_Handled = false;
	};

	class EventDispatcher
	{
		template<typename T>
		using EventFn = std::_Can_call_function_object<bool(T&)>
	public:
		EventDispatcher(Event& event)
			: m_Event(event) 
		{
		}

		template<typename T>
		bool Dispatch(EventFn<T> func)
		{
			if (m_Event.GetEventType() == T::GetStaticType())
			{
				m_Event.mHandled = func(*(T*)&m_Event);
				return true;
			}
			return false;
		}
	private:
		Event& m_Event;
	};
}