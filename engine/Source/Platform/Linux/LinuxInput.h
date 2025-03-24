#pragma once

#include "Platform/Desktop/DesktopInput.h"

namespace Triangl
{
	class LinuxInput : public DesktopInput
	{
	public:
		LinuxInput(void* window);
	};
}
