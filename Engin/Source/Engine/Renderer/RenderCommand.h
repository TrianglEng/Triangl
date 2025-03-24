#pragma once

#include "Renderer/RendererAPI.h"

namespace Triangl
{
	class RenderCommand
	{
	public:
		static void Init()
		{
			s_API = RendererAPI::New();
			s_API->Init();
		}

		static void Clear()
		{
			s_API->Clear();
		}

		static void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
		{
			s_API->SetViewport(x, y, width, height);
		}

		static void SetClearColor(const glm::vec4& color)
		{
			s_API->SetClearColor(color);
		}

		static void SetClearColor(float r, float g, float b, float a)
		{
			s_API->SetClearColor(r, g, b, a);
		}

		static void SetLineWidth(float width)
		{
			s_API->SetLineWidth(width);
		}

		static void DrawIndexed(const Ref<VertexArray>& vertexArray, uint32_t indexCount = 0)
		{
			s_API->DrawIndexed(vertexArray, indexCount);
		}

		static void DrawLines(const Ref<VertexArray>& vertexArray, uint32_t vertexCount)
		{
			s_API->DrawLines(vertexArray, vertexCount);
		}
	private:
		static Scope<RendererAPI> s_API;
	};
}
