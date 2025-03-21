#include "tlpch.hh"
#include "opengl_vertex_array.hh"

#include <glad/glad.h>

namespace triangl {

	static GLenum shader_data_type_to_opengl_type(shader_data_type type)
	{
		switch (type)
		{
		case shader_data_type::float1:
		case shader_data_type::float2:
		case shader_data_type::float3:
		case shader_data_type::float4:
		case shader_data_type::mat3:
		case shader_data_type::mat4:
			return GL_FLOAT;
		case shader_data_type::int1:
		case shader_data_type::int2:
		case shader_data_type::int3:
		case shader_data_type::int4:
			return GL_INT;
		case shader_data_type::boolean:
			return GL_BOOL;
		}

		TL_CORE_ASSERT(false, "unknown shader data type!");
		return 0x0;
	}

	opengl_vertex_array::opengl_vertex_array()
	{
		glCreateVertexArrays(1, &m_rid);
	}

	opengl_vertex_array::~opengl_vertex_array()
	{
		glDeleteVertexArrays(1, &m_rid);
	}

	void opengl_vertex_array::bind() const
	{
		glBindVertexArray(m_rid);
	}

	void opengl_vertex_array::unbind() const
	{
		glBindVertexArray(0);
	}

	void opengl_vertex_array::add_vertex_buffer(const std::shared_ptr<vertex_buffer>& buffer)
	{
		TL_CORE_ASSERT(buffer->get_layout().get_elements().size() > 0, "vertex buffer has no layout!");

		glBindVertexArray(m_rid);
		buffer->bind();

		const buffer_layout& layout = buffer->get_layout();
		for (const buffer_element& element : layout)
		{
			switch (element.type)
			{
			case shader_data_type::float1:
			case shader_data_type::float2:
			case shader_data_type::float3:
			case shader_data_type::float4:
			{
				glEnableVertexAttribArray(m_vertex_buffer_index);
				glVertexAttribPointer(
					m_vertex_buffer_index,
					element.get_component_count(),
					shader_data_type_to_opengl_type(element.type),
					element.normalized,
					(GLsizei) layout.get_stride(),
					(const void*)(element.offset)
				);
				++m_vertex_buffer_index;
				break;
			}
			case shader_data_type::int1:
			case shader_data_type::int2:
			case shader_data_type::int3:
			case shader_data_type::int4:
			case shader_data_type::boolean:
			{
				glEnableVertexAttribArray(m_vertex_buffer_index);
				glVertexAttribIPointer(
					m_vertex_buffer_index,
					element.get_component_count(),
					shader_data_type_to_opengl_type(element.type),
					(GLsizei) layout.get_stride(),
					(const void*)(element.offset)
				);
				++m_vertex_buffer_index;
				break;
			}
			case shader_data_type::mat3:
			case shader_data_type::mat4:
			{
				uint8_t count = element.get_component_count();
				for (uint8_t i = 0; i < count; ++i)
				{
					glEnableVertexAttribArray(m_vertex_buffer_index);
					glVertexAttribPointer(
						m_vertex_buffer_index,
						count,
						shader_data_type_to_opengl_type(element.type),
						element.normalized,
						(GLsizei)layout.get_stride(),
						(const void*)(element.offset + sizeof(float) * count * i)
					);
					glVertexAttribDivisor(m_vertex_buffer_index, 1);
					++m_vertex_buffer_index;
				}
				break;
			}
			default:
				TL_CORE_ASSERT(false, "unknown shader data type!");
				return;
			}
		}

		m_vertex_buffers.push_back(buffer);
	}

	void opengl_vertex_array::set_index_buffer(const std::shared_ptr<index_buffer>& buffer)
	{
		glBindVertexArray(m_rid);
		buffer->bind();

		m_index_buffer = buffer;
	}

}
