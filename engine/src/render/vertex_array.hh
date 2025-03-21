#ifndef TRIANGL_RENDER_VERTEX_ARRAY_HH
#define TRIANGL_RENDER_VERTEX_ARRAY_HH 1

#include "render/buffer.hh"

namespace triangl {

	class vertex_array
	{
	public:
		virtual ~vertex_array() = default;

		virtual void bind() const = 0;
		virtual void unbind() const = 0;

		virtual void add_vertex_buffer(const std::shared_ptr<vertex_buffer>& buffer) = 0;
		virtual void set_index_buffer(const std::shared_ptr<index_buffer>& buffer) = 0;

		virtual const std::vector<std::shared_ptr<vertex_buffer>>& get_vertex_buffers() const = 0;
		virtual const std::shared_ptr<index_buffer>& get_index_buffer() const = 0;

		static std::shared_ptr<vertex_array> create();
	};

}

#endif
