#pragma once

#include "Renderer/VertexArray.h"

namespace Triangl
{
	enum class GraphicsAPI
	{
		None,
		OpenGL
	};
	
	std::string_view GraphicsAPIToString(GraphicsAPI api);

	class RendererAPI
	{
	public:
		virtual ~RendererAPI() = default;

		virtual void Init() = 0;
		virtual void Clear() = 0;
		virtual void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) = 0;
		virtual void SetClearColor(const glm::vec4& color) = 0;
		virtual void SetClearColor(float r, float g, float b, float a) = 0;
		virtual void SetLineWidth(float width) = 0;

		virtual void DrawIndexed(const Ref<VertexArray>& vertexArray, uint32_t indexCount = 0) = 0;
		virtual void DrawLines(const Ref<VertexArray>& vertexArray, uint32_t vertexCount) = 0;

		static GraphicsAPI GetAPI() { return s_API; }
		static Scope<RendererAPI> New();
	private:
		static GraphicsAPI s_API;
	};
}
