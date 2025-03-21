#ifndef TRIANGL_OPENGL_CONTEXT_HH
#define TRIANGL_OPENGL_CONTEXT_HH

#include "render/context.hh"

struct GLFWwindow;

namespace triangl {

	class opengl_context : public graphics_context
	{
	public:
		opengl_context(GLFWwindow* native_window_handle);

		virtual void init() override;
		virtual void swap_buffers() override;
	private:
		GLFWwindow* m_native_window_handle = nullptr;
	};

}

#endif
