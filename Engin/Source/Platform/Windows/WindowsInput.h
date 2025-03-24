#pragma once

#include "Platform/Desktop/DesktopInput.h"

namespace Triangl
{
	class WindowsInput : public DesktopInput
	{
	public:
		WindowsInput(void* window);
	};
}
