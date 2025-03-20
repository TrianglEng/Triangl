#ifndef TRIANGL_INPUT_HH
#define TRIANGL_INPUT_HH 1

#include "core/base.hh"

#include "input/keycodes.hh"
#include "input/mousecodes.hh"

namespace triangl {

	enum class input_state
	{
		pressed   = 1,
		repeating = 2,
		released  = 0
	};

	class native_input
	{
	public:
		virtual ~native_input() = default;
	
		virtual input_state get_key_state(keycode key) const = 0;
		virtual input_state get_mouse_button_state(mousecode button) const = 0;
		virtual glm::vec2 get_mouse_position() const = 0;

		static std::unique_ptr<native_input> create(void* native_window_handle);
	};

	class input
	{
	public:
		static void init();

		static input_state get_key_state(keycode key)
		{
			return s_inst->get_key_state(key);
		}

		static bool is_key_pressed(keycode key)
		{
			return get_key_state(key) == input_state::pressed;
		}

		static bool is_key_repeating(keycode key)
		{
			return get_key_state(key) == input_state::repeating;
		}

		static bool is_key_down(keycode key)
		{
			input_state state = get_key_state(key);
			return state == input_state::pressed || state == input_state::repeating;
		}

		static bool is_key_released(keycode key)
		{
			return get_key_state(key) == input_state::released;
		}

		static input_state get_mouse_button_state(mousecode button)
		{
			return s_inst->get_mouse_button_state(button);
		}

		static bool is_mouse_button_pressed(mousecode button)
		{
			return get_mouse_button_state(button) == input_state::pressed;
		}

		static bool is_mouse_button_released(mousecode button)
		{
			return get_mouse_button_state(button) == input_state::released;
		}

		static glm::vec2 get_mouse_position()
		{
			return s_inst->get_mouse_position();
		}

		static float get_mouse_x()
		{
			return get_mouse_position().x;
		}

		static float get_mouse_y()
		{
			return get_mouse_position().y;
		}
	private:
		static std::unique_ptr<native_input> s_inst;
	};

}

#endif
