#include "TrianglPCH.h"
#include "Window.h"

#include "Platform/Windows/WindowsWindow.h"
#include "Platform/Linux/LinuxWindow.h"

namespace Triangl
{
	Scope<Window> Window::New(const WindowProps& props)
	{
		return MakeScope<TL_MAKE_PLATFORM_TYPE(Window)>(props);
	}
}
