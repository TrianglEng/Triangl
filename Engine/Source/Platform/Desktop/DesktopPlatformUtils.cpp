#include "TrianglPCH.h"
#include "DesktopPlatformUtils.h"

#include <GLFW/glfw3.h>

namespace Triangl
{
	float DesktopPlatformUtils::GetTime() const
	{
		return (float) glfwGetTime();
	}
}
