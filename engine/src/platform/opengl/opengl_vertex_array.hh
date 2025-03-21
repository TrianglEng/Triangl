#ifndef TRIANGL_PLATFORM_OPENGL_VERTEX_ARRAY_HH
#define TRIANGL_PLATFORM_OPENGL_VERTEX_ARRAY_HH 1

#include "render/vertex_array.hh"

namespace triangl {

	class opengl_vertex_array : public vertex_array
	{
	public:
		opengl_vertex_array();
		virtual ~opengl_vertex_array() override;

		virtual void bind() const override;
		virtual void unbind() const override;

		virtual void add_vertex_buffer(const std::shared_ptr<vertex_buffer>& buffer) override;
		virtual void set_index_buffer(const std::shared_ptr<index_buffer>& buffer) override;

		virtual const std::vector<std::shared_ptr<vertex_buffer>>& get_vertex_buffers() const override { return m_vertex_buffers; }
		virtual const std::shared_ptr<index_buffer>& get_index_buffer() const override { return m_index_buffer; }
	private:
		uint32_t m_rid = 0;
		uint32_t m_vertex_buffer_index = 0;

		std::vector<std::shared_ptr<vertex_buffer>> m_vertex_buffers;
		std::shared_ptr<index_buffer> m_index_buffer;
	};

}

#endif
