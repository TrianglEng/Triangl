#include "tlpch.hh"
#include "openglapi.hh"

#include <glad/glad.h>

namespace triangl {

	static void opengl_message_callback(
		unsigned src,
		unsigned type,
		unsigned id,
		unsigned severity,
		int len,
		const char* msg,
		const void* puser
	)
	{
		switch (severity)
		{
		case GL_DEBUG_SEVERITY_HIGH:         TL_CORE_FATAL(msg); break;
		case GL_DEBUG_SEVERITY_MEDIUM:       TL_CORE_ERROR(msg); break;
		case GL_DEBUG_SEVERITY_LOW:          TL_CORE_WARN(msg);  break;
		case GL_DEBUG_SEVERITY_NOTIFICATION: TL_CORE_TRACE(msg); break;
		default:
			TL_CORE_ASSERT(false, "unknown severity!");
			break;
		}
	}

	void opengl_api::init()
	{
	#ifdef TL_TEST_BUILD
		glEnable(GL_DEBUG_OUTPUT);
		glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);

		glDebugMessageCallback(opengl_message_callback, nullptr);
		glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DEBUG_SEVERITY_NOTIFICATION, 0, nullptr, GL_FALSE);
	#endif

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glEnable(GL_DEPTH_TEST);
		glEnable(GL_LINE_SMOOTH);
	}

	void opengl_api::clear()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void opengl_api::set_viewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
	{
		glViewport(x, y, width, height);
	}

	void opengl_api::set_clear_color(const glm::vec4& color)
	{
		set_clear_color(color.r, color.g, color.b, color.a);
	}

	void opengl_api::set_clear_color(float r, float g, float b, float a)
	{
		glClearColor(r, g, b, a);
	}

	void opengl_api::set_line_width(float width)
	{
		glLineWidth(width);
	}

}
