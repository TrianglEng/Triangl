#pragma once

#include "Event/Event.h"
#include "Input/KeyCodes.h"

#include <sstream>

namespace Triangl
{
	class KeyEvent : public Event
	{
	public:
		virtual std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyEvent: " << m_KeyCode;
			return ss.str();
		}

		KeyCode GetKeyCode() const { return m_KeyCode; }
		EVENT_CATEGORY_DETAIL(EC_Input | EC_Keyboard);
	protected:
		KeyEvent(KeyCode keycode)
			: m_KeyCode(keycode) {}
	
		KeyCode m_KeyCode;
	};

	class KeyPressedEvent : public KeyEvent
	{
	public:
		EVENT_TYPE_DETAIL(KeyPressed);

		KeyPressedEvent(KeyCode keycode, bool repeat)
			: KeyEvent(keycode), m_Repeat(repeat) {}

		virtual std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyPressedEvent: " << m_KeyCode << ", " << m_Repeat ? "true" : "false";
			return ss.str();
		}

		bool IsRepeat() const { return m_Repeat; }
	private:
		bool m_Repeat = false;
	};

	class KeyTypedEvent : public KeyEvent
	{
	public:
		EVENT_TYPE_DETAIL(KeyTyped);

		KeyTypedEvent(KeyCode keycode)
			: KeyEvent(keycode) {}

		virtual std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyTypedEvent: " << m_KeyCode;
			return ss.str();
		}
	};

	class KeyReleasedEvent : public KeyEvent
	{
	public:
		EVENT_TYPE_DETAIL(KeyReleased);

		KeyReleasedEvent(KeyCode keycode)
			: KeyEvent(keycode) {}

		virtual std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyReleasedEvent: " << m_KeyCode;
			return ss.str();
		}
	};
}
