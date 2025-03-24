#include "TrianglPCH.h"
#include "OpenGLBuffer.h"

#include <glad/glad.h>

namespace Triangl
{
	static GLuint SetupBuffer(GLenum type, const void* data, GLsizeiptr size, GLenum usage)
	{
		GLuint id;
		glCreateBuffers(1, &id);
		glBindBuffer(type, id);
		glBufferData(type, size, data, usage);
		return id;
	}

	OpenGLVertexBuffer::OpenGLVertexBuffer(size_t size)
	{
		m_RendererID = SetupBuffer(GL_ARRAY_BUFFER, nullptr, size, GL_DYNAMIC_DRAW);
	}

	OpenGLVertexBuffer::OpenGLVertexBuffer(const float* vertices, size_t size)
	{
		m_RendererID = SetupBuffer(GL_ARRAY_BUFFER, vertices, size, GL_STATIC_DRAW);
	}

	OpenGLVertexBuffer::~OpenGLVertexBuffer()
	{
		glDeleteBuffers(1, &m_RendererID);
	}

	void OpenGLVertexBuffer::Bind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
	}

	void OpenGLVertexBuffer::Unbind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void OpenGLVertexBuffer::SetData(const void* data, uint32_t size)
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
		glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
	}

	void OpenGLVertexBuffer::SetLayout(const BufferLayout& layout)
	{
		m_Layout = layout;
	}

	OpenGLIndexBuffer::OpenGLIndexBuffer(const uint32_t* indices, uint32_t count)
		: m_Count(count)
	{
		m_RendererID = SetupBuffer(GL_ELEMENT_ARRAY_BUFFER, indices, count * sizeof(uint32_t), GL_STATIC_DRAW);
	}

	OpenGLIndexBuffer::~OpenGLIndexBuffer()
	{
		glDeleteBuffers(1, &m_RendererID);
	}

	void OpenGLIndexBuffer::Bind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
	}

	void OpenGLIndexBuffer::Unbind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
}
