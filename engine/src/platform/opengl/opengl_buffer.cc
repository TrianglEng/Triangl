#include "tlpch.hh"
#include "opengl_buffer.hh"

#include <glad/glad.h>

namespace triangl {

	static GLuint create_buffer(GLenum type, const void* data, GLsizeiptr size, GLenum usage)
	{
		GLuint id;
		glCreateBuffers(1, &id);
		glBindBuffer(type, id);
		glBufferData(type, size, data, usage);
		return id;
	}

	opengl_vertex_buffer::opengl_vertex_buffer(size_t size)
	{
		m_rid = create_buffer(GL_ARRAY_BUFFER, nullptr, size, GL_DYNAMIC_DRAW);
	}

	opengl_vertex_buffer::opengl_vertex_buffer(const float* vertices, size_t size)
	{
		m_rid = create_buffer(GL_ARRAY_BUFFER, vertices, size, GL_STATIC_DRAW);
	}

	opengl_vertex_buffer::~opengl_vertex_buffer()
	{
		glDeleteBuffers(1, &m_rid);
	}

	void opengl_vertex_buffer::bind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_rid);
	}

	void opengl_vertex_buffer::unbind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void opengl_vertex_buffer::set_data(const void* data, uint32_t size)
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_rid);
		glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
	}

	void opengl_vertex_buffer::set_layout(const buffer_layout& layout)
	{
		m_layout = layout;
	}

	opengl_index_buffer::opengl_index_buffer(const uint32_t* indices, uint32_t count)
		: m_count(count)
	{
		m_rid = create_buffer(GL_ELEMENT_ARRAY_BUFFER, indices, count * sizeof(uint32_t), GL_STATIC_DRAW);
	}

	opengl_index_buffer::~opengl_index_buffer()
	{
		glDeleteBuffers(1, &m_rid);
	}

	void opengl_index_buffer::bind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_rid);
	}

	void opengl_index_buffer::unbind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

}
