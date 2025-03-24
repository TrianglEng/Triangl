#pragma once

#include "Platform/Desktop/DesktopWindow.h"

namespace Triangl
{
	class WindowsWindow : public DesktopWindow
	{
	public:
		WindowsWindow(const WindowProps& props = {});

		virtual bool Init() override;

		bool SetUseImmersiveDarkMove(bool use);
	};
}
