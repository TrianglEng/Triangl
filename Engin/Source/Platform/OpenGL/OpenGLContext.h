#pragma once

#include "Renderer/GraphicsContext.h"

struct GLFWwindow;

namespace Triangl
{
	class OpenGLContext : public GraphicsContext
	{
	public:
		OpenGLContext(GLFWwindow* window);

		virtual void Init() override;
		virtual void SwapBuffers() override;
	private:
		GLFWwindow* m_Window = nullptr;
	};
}
