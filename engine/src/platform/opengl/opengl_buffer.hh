#ifndef TRIANGL_PLATFORM_OPENGL_BUFFER_HH
#define TRIANGL_PLATFORM_OPENGL_BUFFER_HH 1

#include "render/buffer.hh"

namespace triangl {

	class opengl_vertex_buffer : public vertex_buffer
	{
	public:
		opengl_vertex_buffer(size_t size);
		opengl_vertex_buffer(const float* vertices, size_t size);
		virtual ~opengl_vertex_buffer() override;

		virtual void bind() const override;
		virtual void unbind() const override;

		virtual void set_data(const void* data, uint32_t size) override;
		virtual void set_layout(const buffer_layout& layout) override;

		virtual const buffer_layout& get_layout() const override { return m_layout; }
	private:
		uint32_t m_rid = 0;
		buffer_layout m_layout;
	};

	class opengl_index_buffer : public index_buffer
	{
	public:
		opengl_index_buffer(const uint32_t* indices, uint32_t count);
		virtual ~opengl_index_buffer() override;

		virtual void bind() const override;
		virtual void unbind() const override;

		virtual uint32_t get_count() const override { return m_count; }
	private:
		uint32_t m_rid = 0;
		uint32_t m_count = 0;
	};

}

#endif
