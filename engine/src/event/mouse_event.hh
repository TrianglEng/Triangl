#ifndef TRIANGL_MOUSE_EVENT_HH
#define TRIANGL_MOUSE_EVENT_HH

#include "event/event.hh"
#include "input/mousecodes.hh"

#include <sstream>

namespace triangl {

	class mouse_event : public event
	{
	public:
		EVENT_CATEGORY_DETAIL(ec_input | ec_mouse);
	};

	class mouse_moved_event : public mouse_event
	{
	public:
		mouse_moved_event(float xpos, float ypos)
			: m_xpos(xpos), m_ypos(ypos) {}

		virtual std::string to_string() const override
		{
			std::stringstream ss;
			ss << "mouse_moved_event: " << m_xpos << ", " << m_ypos;
			return ss.str();
		}

		float get_xpos() const { return m_xpos; }
		float get_ypos() const { return m_ypos; }

		EVENT_TYPE_DETAIL(mouse_moved);
	private:
		float m_xpos = 0.0f, m_ypos = 0.0f;
	};

	class mouse_scrolled_event : public mouse_event
	{
	public:
		mouse_scrolled_event(float xoff, float yoff)
			: m_xoff(xoff), m_yoff(yoff) {}

		virtual std::string to_string() const override
		{
			std::stringstream ss;
			ss << "mouse_scrolled_event: " << m_xoff << ", " << m_yoff;
			return ss.str();
		}

		float get_xoff() const { return m_xoff; }
		float get_yoff() const { return m_yoff; }

		EVENT_TYPE_DETAIL(mouse_scrolled);
	private:
		float m_xoff = 0.0f, m_yoff = 0.0f;
	};

	class mouse_button_event : public mouse_event
	{
	public:
		mousecode get_button() const { return m_button; }
		EVENT_CATEGORY_DETAIL(ec_input | ec_mouse | ec_mouse_button);
	protected:
		mouse_button_event(mousecode button)
			: m_button(button) {}

		mousecode m_button;
	};

	class mouse_button_pressed_event : public mouse_button_event
	{
	public:
		mouse_button_pressed_event(mousecode button)
			: mouse_button_event(button) {}

		virtual std::string to_string() const override
		{
			std::stringstream ss;
			ss << "mouse_button_pressed_event: " << m_button;
			return ss.str();
		}

		EVENT_TYPE_DETAIL(mouse_button_pressed);
	};
	
	class mouse_button_released_event : public mouse_button_event
	{
	public:
		mouse_button_released_event(mousecode button)
			: mouse_button_event(button) {}

		virtual std::string to_string() const override
		{
			std::stringstream ss;
			ss << "mouse_button_released_event: " << m_button;
			return ss.str();
		}

		EVENT_TYPE_DETAIL(mouse_button_released);
	};

}

#endif
