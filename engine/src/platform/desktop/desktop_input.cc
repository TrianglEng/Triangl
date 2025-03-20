#include "tlpch.hh"
#include "desktop_input.hh"

#include <GLFW/glfw3.h>

namespace triangl {

	desktop_input::desktop_input(void* native_window_handle)
		: m_native_window_handle((GLFWwindow*) native_window_handle)
	{
		TL_CORE_ASSERT(native_window_handle, "input window handle is null!");
	}

	input_state desktop_input::get_key_state(keycode key) const
	{
		return (input_state) glfwGetKey(m_native_window_handle, (keycode) key);
	}

	input_state desktop_input::get_mouse_button_state(mousecode button) const
	{
		return (input_state) glfwGetMouseButton(m_native_window_handle, (mousecode) button);
	}

	glm::vec2 desktop_input::get_mouse_position() const
	{
		double x, y;
		glfwGetCursorPos(m_native_window_handle, &x, &y);
		return { (float) x, (float) y };
	}

}
