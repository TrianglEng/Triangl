#include "tlpch.hh"
#include "desktop_util.hh"

#include <GLFW/glfw3.h>

namespace triangl {

	float desktop_platform_util::get_time() const
	{
		return (float) glfwGetTime();
	}

}
