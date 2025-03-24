#include "TrianglPCH.h"
#include "GraphicsContext.h"

#include "Renderer/RendererAPI.h"
#include "Platform/OpenGL/OpenGLContext.h"

namespace Triangl
{
	Scope<GraphicsContext> GraphicsContext::New(void* window)
	{
		switch (RendererAPI::GetAPI())
		{
		case GraphicsAPI::OpenGL: return MakeScope<OpenGLContext>((GLFWwindow*) window);
		default: break;
		}

		TL_CORE_ASSERT(false, "Unknown GraphicsAPI!");
		return nullptr;
	}
}
