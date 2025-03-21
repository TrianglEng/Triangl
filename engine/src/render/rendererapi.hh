#ifndef TRIANGL_RENDER_RENDERERAPI_HH
#define TRIANGL_RENDER_RENDERERAPI_HH 1

#include "render/vertex_array.hh"

namespace triangl {

	enum class graphics_api
	{
		none,
		opengl
	};

	class renderer_api
	{
	public:
		virtual ~renderer_api() = default;

		virtual void init() = 0;
		virtual void clear() = 0;
		virtual void set_viewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) = 0;
		virtual void set_clear_color(const glm::vec4& color) = 0;
		virtual void set_clear_color(float r, float g, float b, float a) = 0;
		virtual void set_line_width(float width) = 0;

		virtual void draw_indexed(const std::shared_ptr<vertex_array>& vao, uint32_t index_count = 0) = 0;
		virtual void draw_lines(const std::shared_ptr<vertex_array>& vao, uint32_t vertex_count) = 0;

		static graphics_api get_api() { return s_api; }
		static std::unique_ptr<renderer_api> create();
	private:
		static graphics_api s_api;
	};

}

#endif
