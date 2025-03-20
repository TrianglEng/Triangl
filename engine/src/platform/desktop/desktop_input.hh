#ifndef TRIANGL_PLATFORM_DESKTOP_INPUT_HH
#define TRIANGL_PLATFORM_DESKTOP_INPUT_HH 1

#include "input/input.hh"

struct GLFWwindow;

namespace triangl {

	class desktop_input : public native_input
	{
	public:
		desktop_input(void* native_window_handle);

		virtual input_state get_key_state(keycode key) const override;
		virtual input_state get_mouse_button_state(mousecode button) const override;
		virtual glm::vec2 get_mouse_position() const override;
	private:
		GLFWwindow* m_native_window_handle = nullptr;
	};

}

#endif
