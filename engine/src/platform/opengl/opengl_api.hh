#ifndef TRIANGL_OPENGLAPI_HH
#define TRIANGL_OPENGLAPI_HH 1

#include "render/rendererapi.hh"

namespace triangl {

	class opengl_api : public renderer_api
	{
	public:
		virtual void init() override;
		virtual void clear() override;
		virtual void set_viewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) override;
		virtual void set_clear_color(const glm::vec4& color) override;
		virtual void set_clear_color(float r, float g, float b, float a) override;
		virtual void set_line_width(float width) override;
	};

}

#endif
