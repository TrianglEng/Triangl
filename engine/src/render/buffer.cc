#include "tlpch.hh"
#include "buffer.hh"

#include "render/rendererapi.hh"
#include "platform/opengl/opengl_buffer.hh"

namespace triangl {

	size_t sizeof_shader_data_type(shader_data_type type)
	{
		switch (type)
		{
		case shader_data_type::float1:  return 4;
		case shader_data_type::float2:  return 4 * 2;
		case shader_data_type::float3:  return 4 * 3;
		case shader_data_type::float4:  return 4 * 4;
		case shader_data_type::mat3:    return 4 * 3 * 3;
		case shader_data_type::mat4:    return 4 * 4 * 4;
		case shader_data_type::int1:    return 4;
		case shader_data_type::int2:    return 4 * 2;
		case shader_data_type::int3:    return 4 * 3;
		case shader_data_type::int4:    return 4 * 4;
		case shader_data_type::boolean: return 1;
		}

		TL_CORE_ASSERT(false, "unknown shader data type!");
		return 0;
	}

	uint8_t buffer_element::get_component_count() const
	{
		switch (type)
		{
		case shader_data_type::float1:  return 1;
		case shader_data_type::float2:  return 2;
		case shader_data_type::float3:  return 3;
		case shader_data_type::float4:  return 4;
		case shader_data_type::mat3:    return 3;
		case shader_data_type::mat4:    return 4;
		case shader_data_type::int1:    return 1;
		case shader_data_type::int2:    return 2;
		case shader_data_type::int3:    return 3;
		case shader_data_type::int4:    return 4;
		case shader_data_type::boolean: return 1;
		}

		TL_CORE_ASSERT(false, "unknown shader data type!");
		return 0;
	}

	std::shared_ptr<vertex_buffer> vertex_buffer::create(size_t size)
	{
		switch (renderer_api::get_api())
		{
		case graphics_api::opengl: return std::make_unique<opengl_vertex_buffer>(size);
		default: break;
		}

		TL_CORE_ASSERT(false, "unknown graphics_api!");
		return nullptr;
	}

	std::shared_ptr<vertex_buffer> vertex_buffer::create(const float* vertices, size_t size)
	{
		switch (renderer_api::get_api())
		{
		case graphics_api::opengl: return std::make_unique<opengl_vertex_buffer>(vertices, size);
		default: break;
		}

		TL_CORE_ASSERT(false, "unknown graphics_api!");
		return nullptr;
	}

	std::shared_ptr<index_buffer> index_buffer::create(const uint32_t* indices, uint32_t count)
	{
		switch (renderer_api::get_api())
		{
		case graphics_api::opengl: return std::make_unique<opengl_index_buffer>(indices, count);
		default: break;
		}

		TL_CORE_ASSERT(false, "unknown graphics_api!");
		return nullptr;
	}

}
