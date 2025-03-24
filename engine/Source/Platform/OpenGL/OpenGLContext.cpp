#include "TrianglPCH.h"
#include "OpenGLContext.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Triangl
{
	const int c_MajorVerGL = 4, c_MinorVerGL = 5;

	OpenGLContext::OpenGLContext(GLFWwindow* window)
		: m_Window(window)
	{
		TL_CORE_ASSERT(window, "Unknown context window handle!");
	}

	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(m_Window);

		if (glfwGetCurrentContext() == m_Window)
		{
			TL_CORE_INFO("The OpenGL context has been created!");
		}
		else
		{
			TL_CORE_FATAL("Failed to create the OpenGL context!");
		}

		if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
		{
			TL_CORE_FATAL("Failed to initialize Glad (OpenGL initialization/function load failure)!");
		}
		TL_CORE_INFO("Glad has been initialized successfuly (initialized OpenGL/loaded functions).");

		TL_CORE_INFO("OpenGL Info:");
		TL_CORE_INFO("  Vendor:       {}", (const char*) glGetString(GL_VENDOR));
		TL_CORE_INFO("  Renderer:     {}", (const char*) glGetString(GL_RENDERER));
		TL_CORE_INFO("  Version:      {}", (const char*) glGetString(GL_VERSION));
		TL_CORE_INFO("  GLSL Version: {}", (const char*) glGetString(GL_SHADING_LANGUAGE_VERSION));

		if (GLVersion.major < c_MajorVerGL || (GLVersion.major == c_MajorVerGL && GLVersion.minor < c_MinorVerGL))
		{
			TL_CORE_FATAL
			(
				"The current renderer '{}' (GPU/video card etc.) that owns the OpenGL graphics context has up to OpenGL version {}.{} support.\n\n"
				"Triangl Engine (the underlying software for this application) requires a renderer with at least OpenGL version {}.{} support. "
				"This renderer, currently as-is isn't compatible with Triangl Engine.\n\n"
				"Possible fixes include:\n"
				"  - Updating the graphics driver for the renderer, newer versions of the driver might have introduced support for newer OpenGL versions.\n"
				"  - Changing the renderer to another one, if such exists and is available that supports the required OpenGL functionality.\n\n"
				"If none of these are applicable, this application cannot be officially run on this device with this configuration.",
				(const char*) glGetString(GL_RENDERER), GLVersion.major, GLVersion.minor, c_MajorVerGL, c_MinorVerGL
			);
		}
	}

	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_Window);
	}
}
