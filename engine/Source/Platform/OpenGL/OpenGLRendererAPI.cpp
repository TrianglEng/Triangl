#include "TrianglPCH.h"
#include "OpenGLRendererAPI.h"

#include <glad/glad.h>

namespace Triangl
{
	static void OpenGLMessageCallback
	(
		unsigned source,
		unsigned type,
		unsigned id,
		unsigned severity,
		int length,
		const char* msg,
		const void* userParam
	)
	{
		switch (severity)
		{
		case GL_DEBUG_SEVERITY_HIGH:         TL_CORE_FATAL(msg); break;
		case GL_DEBUG_SEVERITY_MEDIUM:       TL_CORE_ERROR(msg); break;
		case GL_DEBUG_SEVERITY_LOW:          TL_CORE_WARN(msg);  break;
		case GL_DEBUG_SEVERITY_NOTIFICATION: TL_CORE_TRACE(msg); break;
		default:
			TL_CORE_ASSERT(false, "Unknown OpenGL message severity!");
			break;
		}
	}

	void OpenGLRendererAPI::Init()
	{
	#ifdef TL_TEST_BUILD
		glEnable(GL_DEBUG_OUTPUT);
		glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);

		glDebugMessageCallback(OpenGLMessageCallback, nullptr);
		glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DEBUG_SEVERITY_NOTIFICATION, 0, nullptr, GL_FALSE);
	#endif

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glEnable(GL_DEPTH_TEST);
		glEnable(GL_LINE_SMOOTH);
	}

	void OpenGLRendererAPI::Clear()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void OpenGLRendererAPI::SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
	{
		glViewport(x, y, width, height);
	}

	void OpenGLRendererAPI::SetClearColor(const glm::vec4& color)
	{
		SetClearColor(color.r, color.g, color.b, color.a);
	}

	void OpenGLRendererAPI::SetClearColor(float r, float g, float b, float a)
	{
		glClearColor(r, g, b, a);
	}

	void OpenGLRendererAPI::SetLineWidth(float width)
	{
		glLineWidth(width);
	}

	void OpenGLRendererAPI::DrawIndexed(const Ref<VertexArray>& vertexArray, uint32_t indexCount)
	{
		uint32_t count = indexCount ? indexCount : vertexArray->GetIndexBuffer()->GetCount();
		vertexArray->Bind();

		glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);
	}

	void OpenGLRendererAPI::DrawLines(const Ref<VertexArray>& vertexArray, uint32_t vertexCount)
	{
		vertexArray->Bind();
		glDrawArrays(GL_LINES, 0, vertexCount);
	}
}
