#include "TrianglPCH.h"
#include "RendererAPI.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Triangl
{
	GraphicsAPI RendererAPI::s_API = GraphicsAPI::OpenGL;

	std::string_view GraphicsAPIToString(GraphicsAPI api)
	{
		switch (api)
		{
		case GraphicsAPI::OpenGL: return "GraphicsAPI::OpenGL";
		}

		TL_CORE_ASSERT(false, "Unknown GraphicsAPI!");
		return {};
	}

	Scope<RendererAPI> RendererAPI::New()
	{
		switch (s_API)
		{
		case GraphicsAPI::OpenGL: return MakeScope<OpenGLRendererAPI>();
		default: break;
		}
		
		TL_CORE_ASSERT(false, "Unknown GraphicsAPI!");
		return nullptr;
	}
}
