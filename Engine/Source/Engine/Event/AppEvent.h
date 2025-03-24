#pragma once

#include "Event/Event.h"

#include <sstream>

namespace Triangl
{
	class AppEvent : public Event
	{
	public:
		EVENT_CATEGORY_DETAIL(EC_Application);
	};
	
	class WindowClosedEvent : public AppEvent
	{
	public:
		EVENT_TYPE_DETAIL(WindowClosed);
	};

	class WindowResizedEvent : public AppEvent
	{
	public:
		WindowResizedEvent(int width, int height)
			: m_Width(width), m_Height(height) {}

		virtual std::string ToString() const override
		{
			std::stringstream ss;
			ss << "WindowResizedEvent: " << m_Width << ", " << m_Height;
			return ss.str();
		}

		EVENT_TYPE_DETAIL(WindowResized);
	private:
		int m_Width = 0, m_Height = 0;
	};

	class WindowFocusedEvent : public AppEvent
	{
	public:
		EVENT_TYPE_DETAIL(WindowFocused);
	};

	class WindowLostFocusEvent : public AppEvent
	{
	public:
		EVENT_TYPE_DETAIL(WindowLostFocus);
	};
}
