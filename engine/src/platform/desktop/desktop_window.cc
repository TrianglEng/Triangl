#include "tlpch.hh"
#include "desktop_window.hh"

#include "event/app_event.hh"
#include "event/key_event.hh"
#include "event/mouse_event.hh"

#include "render/rendererapi.hh"

#include <GLFW/glfw3.h>

namespace triangl {

	static uint16_t s_window_count = 0;

	static void glfw_error_callback(
		int code,
		const char* msg
	)
	{
		TL_CORE_ERROR("glfw error ({}): {}", code, msg);
	}

	desktop_window::desktop_window(const window_props& props)
		: m_data
		  {
		      props.title,
			  props.width,
			  props.height,
			  props.fullscreen,
			  props.resizable,
			  props.vsync,
			  nullptr,
			  window_closed,
			  window_resized,
			  window_focused,
			  window_lost_focus,
			  key_pressed,
			  key_typed,
			  key_released,
			  mouse_moved,
			  mouse_scrolled,
			  mouse_button_pressed,
			  mouse_button_released
		  }
	{
	}

	desktop_window::~desktop_window()
	{
		if (is_open())
		{
			destroy();
		}
	}

	bool desktop_window::init()
	{
		
		if (is_open())
		{
			TL_CORE_WARN("tried to initialize window but the window is already open, discarding request");
			return false;
		}

		TL_CORE_INFO("creating window '{}' ({}x{})", m_data.title, m_data.width, m_data.height);

		if (s_window_count == 0)
		{
			if (!glfwInit())
			{
				const char* msg{};
				int code = glfwGetError(&msg);

				TL_CORE_ERROR("failed to initialize glfw! glfw error ({}): {}", code, msg);
				return false;
			}
			TL_CORE_TRACE("glfw initialized successfully.");
			glfwSetErrorCallback(glfw_error_callback);
		}
		else
		{
			TL_CORE_TRACE("glfw already initialized, skipped...");
		}

		switch (renderer_api::get_api())
		{
		case graphics_api::opengl:
		{
			glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API);
		#ifdef TL_TEST_BUILD
			glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
		#endif
			break;
		}
		}
		glfwWindowHint(GLFW_RESIZABLE, m_data.resizable);

		auto failrevert = [this]()
		{
			if (s_window_count == 0)
			{
				glfwTerminate();
			}

			if (m_handle)
			{
				glfwDestroyWindow(m_handle);
			}
		};

		GLFWmonitor* monitor = m_data.fullscreen ? glfwGetPrimaryMonitor() : nullptr;
		m_handle = glfwCreateWindow(
			m_data.width,
			m_data.height,
			m_data.title.c_str(),
			monitor,
			nullptr
		);
		
		if (!m_handle)
		{
			TL_CORE_ERROR("failed to create glfw window!");
			failrevert();
			return false;
		}

		m_context = graphics_context::create(m_handle);
		m_context->init();

		glfwSetWindowUserPointer(m_handle, &m_data);
		set_vsync(m_data.vsync); // set flag

		glfwSetWindowCloseCallback(m_handle, [](GLFWwindow* window)
		{
			window_data& data = *(window_data*) glfwGetWindowUserPointer(window);
			
			window_closed_event e;
			data.callback(e);

			data.window_closed.send();
		});
		
		glfwSetWindowSizeCallback(m_handle, [](GLFWwindow* window, int width, int height)
		{
			window_data& data = *(window_data*) glfwGetWindowUserPointer(window);
			
			data.width = width;
			data.height = height;

			window_resized_event e(width, height);
			data.callback(e);

			data.window_resized.send(width, height);
		});

		glfwSetWindowFocusCallback(m_handle, [](GLFWwindow* window, int focused)
		{
			window_data& data = *(window_data*) glfwGetWindowUserPointer(window);
			
			if (focused)
			{
				window_focused_event e;
				data.callback(e);

				data.window_focused.send();
			}
			else
			{
				window_lost_focus_event e;
				data.callback(e);

				data.window_lost_focus.send();
			}
		});
		
		glfwSetKeyCallback(m_handle, [](GLFWwindow* window, int key, int scancode, int action, int mods)
		{
			window_data& data = *(window_data*) glfwGetWindowUserPointer(window);

			switch (action)
			{
			case GLFW_PRESS:
			{
				key_pressed_event e((keycode) key, false);
				data.callback(e);
				
				data.key_pressed.send((keycode) key, false);
				break;
			}
			case GLFW_REPEAT:
			{
				key_pressed_event e((keycode) key, true);
				data.callback(e);
				
				data.key_pressed.send((keycode) key, true);
				break;
			}
			case GLFW_RELEASE:
			{
				key_released_event e((keycode) key);
				data.callback(e);
				
				data.key_released.send((keycode) key);
				break;
			}
			}
		});

		glfwSetCharCallback(m_handle, [](GLFWwindow* window, unsigned int key)
		{
			window_data& data = *(window_data*) glfwGetWindowUserPointer(window);

			key_typed_event e((keycode) key);
			data.callback(e);

			data.key_typed.send((keycode) key);
		});

		glfwSetCursorPosCallback(m_handle, [](GLFWwindow* window, double xpos, double ypos)
		{
			window_data& data = *(window_data*) glfwGetWindowUserPointer(window);

			mouse_moved_event e((float) xpos, (float) ypos);
			data.callback(e);

			data.mouse_moved.send((float) xpos, (float) ypos);
		});

		glfwSetScrollCallback(m_handle, [](GLFWwindow* window, double xoff, double yoff)
		{
			window_data& data = *(window_data*) glfwGetWindowUserPointer(window);

			mouse_scrolled_event e((float) xoff, (float) yoff);
			data.callback(e);

			data.mouse_scrolled.send((float) xoff, (float) yoff);
		});
		
		glfwSetMouseButtonCallback(m_handle, [](GLFWwindow* window, int button, int action, int mods)
		{
			window_data& data = *(window_data*) glfwGetWindowUserPointer(window);

			switch (action)
			{
			case GLFW_PRESS:
			{
				mouse_button_pressed_event e((mousecode) button);
				data.callback(e);

				data.mouse_button_pressed.send((mousecode) button);
				break;
			}
			case GLFW_RELEASE:
			{
				mouse_button_released_event e((mousecode) button);
				data.callback(e);

				data.mouse_button_released.send((mousecode) button);
				break;
			}
			}
		});
		
		++s_window_count;
		return true;
	}

	bool desktop_window::is_open() const
	{
		return m_handle && !glfwWindowShouldClose(m_handle);
	}

	void desktop_window::update()
	{
		glfwPollEvents();
		m_context->swap_buffers();
	}

	bool desktop_window::destroy()
	{
		if (!is_open())
		{
			TL_CORE_WARN("window got destroy called, but already isn't open, ignoring request.");
			return false;
		}

		glfwDestroyWindow(m_handle);
		m_handle = nullptr;

		if (--s_window_count == 0)
		{
			TL_CORE_TRACE("all windows destroyed, terminating glfw...");
			glfwTerminate();
			TL_CORE_INFO("terminated glfw.");
		}

		return true;
	}

	void desktop_window::set_title(std::string_view title)
	{
		m_data.title = title;
		glfwSetWindowTitle(m_handle, title.data());
	}

	void desktop_window::set_size(int width, int height)
	{
		glfwSetWindowSize(m_handle, width, height);
	}

	void desktop_window::set_width(int width)
	{
		set_size(width, m_data.height);
	}

	void desktop_window::set_height(int height)
	{
		set_size(m_data.width, height);
	}

	void desktop_window::set_vsync(bool vsync)
	{
		m_data.vsync = vsync;
		glfwSwapInterval(vsync ? 1 : 0);
	}

	void desktop_window::set_event_callback(event_callback_fn fn)
	{
		m_data.event_callback = fn;
	}

	void desktop_window::iconify()
	{
		glfwIconifyWindow(m_handle);
	}

	void desktop_window::maximize()
	{
		glfwMaximizeWindow(m_handle);
	}

	void desktop_window::focus()
	{
		glfwFocusWindow(m_handle);
	}

	void desktop_window::request_attention()
	{
		glfwRequestWindowAttention(m_handle);
	}

	bool desktop_window::is_iconified() const
	{
		return glfwGetWindowAttrib(m_handle, GLFW_ICONIFIED);
	}

	bool desktop_window::is_maximized() const
	{
		return glfwGetWindowAttrib(m_handle, GLFW_MAXIMIZED);
	}

	bool desktop_window::is_focused() const
	{
		return glfwGetWindowAttrib(m_handle, GLFW_FOCUSED);
	}

}
