#include "tlpch.hh"
#include "context.hh"

#include "render/rendererapi.hh"
#include "platform/opengl/opengl_context.hh"

namespace triangl {

	std::unique_ptr<graphics_context> graphics_context::create(void* native_window_handle)
	{
		switch (renderer_api::get_api())
		{
		case graphics_api::opengl: return std::make_unique<opengl_context>((GLFWwindow*) native_window_handle);
		default: break;
		}

		TL_CORE_ASSERT(false, "unknown graphics_api!");
		return nullptr;
	}

}
