#include "tlpch.hh"
#include "rendererapi.hh"

#include "platform/opengl/openglapi.hh"

namespace triangl {

	graphics_api renderer_api::s_api = graphics_api::opengl;

	std::unique_ptr<renderer_api> renderer_api::create()
	{
		switch (s_api)
		{
		case graphics_api::opengl: return std::make_unique<opengl_api>();
		default: break;
		}
		
		TL_CORE_ASSERT(false, "unknown graphics_api!");
		return nullptr;
	}

}
