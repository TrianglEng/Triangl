#include "TrianglPCH.h"
#include "Renderer.h"

#include "Renderer/RenderCommand.h"

namespace Triangl
{
	void Renderer::Init()
	{
		RenderCommand::Init();
		TL_CORE_INFO("Renderer: Initialized RenderCommand interface (RendererAPI container).");
	}

	void Renderer::OnWindowResize(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
	{
		RenderCommand::SetViewport(x, y, width, height);
	}
}
