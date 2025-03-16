#ifndef TRIANGL_KEY_EVENT_HH
#define TRIANGL_KEY_EVENT_HH 1

#include "event/event.hh"
#include "input/keycodes.hh"

#include <sstream>

namespace triangl {

	class key_event : public event
	{
	public:
		keycode get_key() const { return m_key; }
		EVENT_CATEGORY_DETAIL(ec_input | ec_keyboard);
	protected:
		key_event(keycode key)
			: m_key(key) {}
	
		keycode m_key;
	};

	class key_pressed_event : public key_event
	{
	public:
		EVENT_TYPE_DETAIL(key_pressed);

		key_pressed_event(keycode key, bool repeat)
			: key_event(key), m_repeat(repeat) {}

		virtual std::string to_string() const override
		{
			std::stringstream ss;
			ss << "key_pressed_event: " << m_key << ", " << m_repeat ? "true" : "false";
			return ss.str();
		}

		bool is_repeat() const { return m_repeat; }
	private:
		bool m_repeat = false;
	};

	class key_typed_event : public key_event
	{
	public:
		EVENT_TYPE_DETAIL(key_typed);

		key_typed_event(keycode key)
			: key_event(key) {}

		virtual std::string to_string() const override
		{
			std::stringstream ss;
			ss << "key_typed_event: " << m_key;
			return ss.str();
		}
	};

	class key_released_event : public key_event
	{
	public:
		EVENT_TYPE_DETAIL(key_released);

		key_released_event(keycode key)
			: key_event(key) {}

		virtual std::string to_string() const override
		{
			std::stringstream ss;
			ss << "key_released_event: " << m_key;
			return ss.str();
		}
	};

}

#endif
