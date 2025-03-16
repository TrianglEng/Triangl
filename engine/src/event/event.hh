#ifndef TRIANGL_EVENT_HH
#define TRIANGL_EVENT_HH

#include "core/base.hh"

namespace triangl {

	enum class event_type
	{
		window_closed, window_resized, window_focused, window_lost_focus,
		key_pressed, key_typed, key_released,
		mouse_moved, mouse_scrolled, mouse_button_pressed, mouse_button_released
	};

	enum event_category
	{
		ec_none         = 0,
		ec_application  = TL_BIT(0),
		ec_input        = TL_BIT(1),
		ec_keyboard     = TL_BIT(2),
		ec_mouse        = TL_BIT(3),
		ec_mouse_button = TL_BIT(4)
	};

	#define EVENT_TYPE_DETAIL(type) \
		static event_type get_static_event_type() { return ::triangl::event_type::##type; } \
		virtual event_type get_event_type() const override { return get_static_event_type(); } \
		virtual std::string_view get_name() const override { return #type; }

	#define EVENT_CATEGORY_DETAIL(flags) virtual int get_category_flags() const override { return flags; }

	class event
	{
	public:
		bool handled = false;
	public:
		virtual ~event() = default;

		virtual event_type get_event_type() const = 0;
		virtual std::string_view get_name() const = 0;
		virtual int get_category_flags() const = 0;
		virtual std::string to_string() const
		{
			return get_name().data();
		}

		bool is_in_category(int category)
		{
			return get_category_flags() & category;
		}
	};

	class event_dispatcher
	{
	public:
		event_dispatcher(event& e)
			: m_event(e) {}

		template <typename T, typename F>
		bool dispatch(const F& func)
		{
			if (m_event.get_event_type() == T::get_static_event_type())
			{
				m_event.handled |= func((T&) m_event);
				return true;
			}
			return false;
		}
	private:
		event& m_event;
	};

	template <typename O>
	inline O& operator<<(O& stream, const event& e)
	{
		return stream << e.to_string();
	}

}

#endif
