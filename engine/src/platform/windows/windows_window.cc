#include "tlpch.hh"
#include "windows_window.hh"

#include "util/platformutil.hh"

#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>

#include <dwmapi.h>

namespace triangl {

	windows_window::windows_window(const window_props& props)
		: desktop_window(props)
	{
	}

	bool windows_window::init()
	{
		if (!desktop_window::init())
		{
			return false;
		}

		if (platform_util::get_system_theme() == system_theme::dark)
		{
			TL_CORE_TRACE("system theme is dark, requesting dwm to use immersive dark mode...");
			if (set_immersive_dark_mode(true))
			{
				TL_CORE_TRACE("successfully set to use immersive dark mode");
			}
			else
			{
				TL_CORE_WARN("dwm requested error hresult code while trying to use immersive dark mode, title bar won't match system theme");
			}
		}

		glfwSetThemeCallback(m_handle, [](GLFWwindow* handle, int theme)
		{
			window_data& data = *(window_data*) glfwGetWindowUserPointer(handle);
			((windows_window*) data.self)->set_immersive_dark_mode(platform_util::get_system_theme() == system_theme::dark);
		});

		return true;
	}

	bool windows_window::set_immersive_dark_mode(bool use)
	{
		HWND hWnd = glfwGetWin32Window(m_handle);
		BOOL bUseDarkMode = use;
		HRESULT hResult = DwmSetWindowAttribute(hWnd, DWMWA_USE_IMMERSIVE_DARK_MODE, &bUseDarkMode, sizeof(bUseDarkMode));

		return hResult == S_OK;
	}

}
