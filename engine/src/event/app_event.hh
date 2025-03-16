#ifndef TRIANGL_APP_EVENT_HH
#define TRIANGL_APP_EVENT_HH 1

#include "event/event.hh"

#include <sstream>

namespace triangl {

	class app_event : public event
	{
	public:
		EVENT_CATEGORY_DETAIL(ec_application);
	};
	
	class window_closed_event : public app_event
	{
	public:
		EVENT_TYPE_DETAIL(window_closed);
	};

	class window_resized_event : public app_event
	{
	public:
		window_resized_event(int width, int height)
			: m_width(width), m_height(height) {}

		virtual std::string to_string() const override
		{
			std::stringstream ss;
			ss << "window_resized_event: " << m_width << ", " << m_height;
			return ss.str();
		}

		EVENT_TYPE_DETAIL(window_resized);
	private:
		int m_width, m_height;
	};

	class window_focused_event : public app_event
	{
	public:
		EVENT_TYPE_DETAIL(window_focused);
	};

	class window_lost_focus_event : public app_event
	{
	public:
		EVENT_TYPE_DETAIL(window_lost_focus);
	};

}

#endif
