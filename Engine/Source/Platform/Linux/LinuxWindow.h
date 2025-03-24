#pragma once

#include "Platform/Desktop/DesktopWindow.h"

namespace Triangl
{
	class LinuxWindow : public DesktopWindow
	{
	public:
		LinuxWindow(const WindowProps& props = {});
	};
}
