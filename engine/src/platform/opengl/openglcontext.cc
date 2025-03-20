#include "tlpch.hh"
#include "openglcontext.hh"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace triangl {

	const int ngc_min_gl_version_major = 4, ngc_min_gl_version_minor = 5;

	opengl_context::opengl_context(GLFWwindow* native_window_handle)
		: m_native_window_handle(native_window_handle)
	{
		TL_CORE_ASSERT(m_native_window_handle, "unknown native window handle!");
	}

	void opengl_context::init()
	{
		glfwMakeContextCurrent(m_native_window_handle);

		if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
		{
			TL_CORE_FATAL("failed to initialize glad (opengl initialization failure)!");
		}

		TL_CORE_INFO("opengl info:");
		TL_CORE_INFO("  vendor:       {}", (const char*) glGetString(GL_VENDOR));
		TL_CORE_INFO("  renderer:     {}", (const char*) glGetString(GL_RENDERER));
		TL_CORE_INFO("  version:      {}", (const char*) glGetString(GL_VERSION));
		TL_CORE_INFO("  glsl version: {}", (const char*) glGetString(GL_SHADING_LANGUAGE_VERSION));

		if (GLVersion.major < ngc_min_gl_version_major || (GLVersion.major == ngc_min_gl_version_major && GLVersion.minor < ngc_min_gl_version_minor))
		{
			TL_CORE_FATAL
			(
				"the current renderer (gpu/video card) '{}' only supports up to opengl version {}.{}. "
				"triangl engine needs a renderer with at least opengl {}.{} functionality. "
				"check if there are driver updates for this renderer or try changing to another renderer which supports the minimum version.",
				(const char*) glGetString(GL_RENDERER), GLVersion.major, GLVersion.minor,
				ngc_min_gl_version_major, ngc_min_gl_version_minor
			);
		}
	}

	void opengl_context::swap_buffers()
	{
		glfwSwapBuffers(m_native_window_handle);
	}

}
