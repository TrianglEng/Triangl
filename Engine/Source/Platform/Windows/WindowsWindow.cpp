#include "TrianglPCH.h"
#include "WindowsWindow.h"

#include "Utils/PlatformUtils.h"

#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>

#define DWMWA_USE_IMMERSIVE_DARK_MODE_PRE  20
#define DWMWA_USE_IMMERSIVE_DARK_MODE_POST 19
#include <dwmapi.h>

namespace Triangl
{
	WindowsWindow::WindowsWindow(const WindowProps& props)
		: DesktopWindow(props)
	{
	}

	bool WindowsWindow::Init()
	{
		if (!DesktopWindow::Init())
		{
			return false;
		}

		if (PlatformUtils::GetSystemTheme() == SystemTheme::Dark)
		{
			TL_CORE_TRACE("WindowsWindow PostDesktopInit: Current system theme is dark, requesting DWM to use immersive dark mode...");
			if (SetUseImmersiveDarkMove(true))
			{
				TL_CORE_INFO("WindowsWindow PostDesktopInit: Successfully set to use immersive dark mode.");
			}
			else
			{
				TL_CORE_WARN("WindowsWindow PostDesktopInit: Failed to change to use immersive dark mode, DWM retuned non-ok HRESULT error code! Title bar will be in light theme.");
			}
		}

		glfwSetThemeCallback(m_Handle, [](GLFWwindow* window, int theme)
		{
			WindowsWindow* wnd = (WindowsWindow*) glfwGetWindowUserPointer(window);
			wnd->SetUseImmersiveDarkMove(PlatformUtils::GetSystemTheme() == SystemTheme::Dark);
		});

		return true;
	}

	bool WindowsWindow::SetUseImmersiveDarkMove(bool use)
	{
		HWND hWnd = glfwGetWin32Window(m_Handle);

		BOOL bUseDarkMode = use;
		HRESULT hResult = DwmSetWindowAttribute(hWnd, DWMWA_USE_IMMERSIVE_DARK_MODE_PRE, &bUseDarkMode, sizeof(BOOL));
		if (hResult != S_OK)
		{
			hResult = DwmSetWindowAttribute(hWnd, DWMWA_USE_IMMERSIVE_DARK_MODE_POST, &bUseDarkMode, sizeof(BOOL));
		}

		// Forces a titlebar redraw, some Win10 versions seem to need this as the titlebar becomes dark after the focus is lost.
		// However, on Win11 this is not an issue and it applies the theme immediately. We still got this here for Win10.
		SendMessage(hWnd, WM_NCACTIVATE, FALSE, NULL);
		SendMessage(hWnd, WM_NCACTIVATE, TRUE, NULL);

		return hResult == S_OK;
	}
}
