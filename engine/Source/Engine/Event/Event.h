#pragma once

#include "Core/Base.h"

namespace Triangl
{
	enum class EventType
	{
		WindowClosed, WindowResized, WindowFocused, WindowLostFocus,
		KeyPressed, KeyTyped, KeyReleased,
		MouseMoved, MouseScrolled, MouseButtonPressed, MouseButtonReleased
	};

	enum EventCategory
	{
		EC_None         = 0,
		EC_Application  = TL_BIT(0),
		EC_Input        = TL_BIT(1),
		EC_Keyboard     = TL_BIT(2),
		EC_Mouse        = TL_BIT(3),
		EC_Mouse_Button = TL_BIT(4)
	};

	#define EVENT_TYPE_DETAIL(type) \
		static EventType GetStaticEventType() { return ::Triangl::EventType::type; } \
		virtual EventType GetEventType() const override { return GetStaticEventType(); } \
		virtual std::string_view GetName() const override { return #type; }

	#define EVENT_CATEGORY_DETAIL(flags) virtual int GetCategoryFlags() const override { return flags; }

	class Event
	{
	public:
		bool Handled = false;
	public:
		virtual ~Event() = default;

		virtual EventType GetEventType() const = 0;
		virtual std::string_view GetName() const = 0;
		virtual int GetCategoryFlags() const = 0;
		virtual std::string ToString() const
		{
			return GetName().data();
		}

		bool IsInCategory(int category)
		{
			return GetCategoryFlags() & category;
		}
	};

	class EventDispatcher
	{
	public:
		EventDispatcher(Event& e)
			: m_Event(e) {}

		template <typename T, typename F>
		bool Dispatch(const F& func)
		{
			if (m_Event.GetEventType() == T::GetStaticEventType())
			{
				m_Event.Handled |= func((T&) m_Event);
				return true;
			}
			return false;
		}
	private:
		Event& m_Event;
	};

	template <typename OStream>
	inline OStream& operator<<(OStream& stream, const Event& e)
	{
		return stream << e.ToString();
	}
}
