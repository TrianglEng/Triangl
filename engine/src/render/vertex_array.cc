#include "tlpch.hh"
#include "vertex_array.hh"

#include "render/rendererapi.hh"
#include "platform/opengl/opengl_vertex_array.hh"

namespace triangl {

	std::shared_ptr<vertex_array> vertex_array::create()
	{
		switch (renderer_api::get_api())
		{
		case graphics_api::opengl: return std::make_unique<opengl_vertex_array>();
		default: break;
		}

		TL_CORE_ASSERT(false, "unknown graphics_api!");
		return nullptr;
	}

}
