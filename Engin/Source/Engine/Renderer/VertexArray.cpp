#include "TrianglPCH.h"
#include "VertexArray.h"

#include "Renderer/RendererAPI.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace Triangl
{
	Ref<VertexArray> VertexArray::New()
	{
		switch (RendererAPI::GetAPI())
		{
		case GraphicsAPI::OpenGL: return MakeRef<OpenGLVertexArray>();
		default: break;
		}

		TL_CORE_ASSERT(false, "unknown graphics_api!");
		return nullptr;
	}
}
