#ifndef TRIANGL_RENDER_BUFFER_HH
#define TRIANGL_RENDER_BUFFER_HH 1

#include "core/base.hh"

namespace triangl {

	enum class shader_data_type
	{
		none = 0,
		float1, float2, float3, float4,
		mat3, mat4,
		int1, int2, int3, int4,
		boolean
	};

	size_t sizeof_shader_data_type(shader_data_type type);

	struct buffer_element
	{
		std::string name;
		shader_data_type type = shader_data_type::none;
		size_t size = 0, offset = 0;
		bool normalized = false;

		buffer_element(shader_data_type type, std::string_view name, bool normalized = false)
			: name(name), type(type), size(sizeof_shader_data_type(type)), offset(0), normalized(normalized) {}

		uint8_t get_component_count() const;
	};

	class buffer_layout
	{
	public:
		buffer_layout() = default;
		buffer_layout(std::initializer_list<buffer_element> elements)
			: m_elements(elements)
		{
			recalculate_element_offsets_and_stride();
		}

		std::vector<buffer_element>::iterator begin() { return m_elements.begin(); }
		std::vector<buffer_element>::iterator end() { return m_elements.end(); }
		std::vector<buffer_element>::const_iterator begin() const { return m_elements.begin(); }
		std::vector<buffer_element>::const_iterator end() const { return m_elements.end(); }
		std::vector<buffer_element>::const_iterator cbegin() const { return m_elements.begin(); }
		std::vector<buffer_element>::const_iterator cend() const { return m_elements.end(); }
		std::vector<buffer_element>::reverse_iterator rbegin() { return m_elements.rbegin(); }
		std::vector<buffer_element>::reverse_iterator rend() { return m_elements.rend(); }
		std::vector<buffer_element>::const_reverse_iterator rbegin() const { return m_elements.rbegin(); }
		std::vector<buffer_element>::const_reverse_iterator rend() const { return m_elements.rend(); }
		std::vector<buffer_element>::const_reverse_iterator crbegin() const { return m_elements.crbegin(); }
		std::vector<buffer_element>::const_reverse_iterator crend() const { return m_elements.crend(); }

		const std::vector<buffer_element>& get_elements() const { return m_elements; }
		size_t get_stride() const { return m_stride; }
	private:
		void recalculate_element_offsets_and_stride()
		{
			m_stride = 0;
			for (buffer_element& element : m_elements)
			{
				element.offset = m_stride;
				m_stride += element.size;
			}
		}
	private:
		std::vector<buffer_element> m_elements;
		size_t m_stride = 0;
	};

	class vertex_buffer
	{
	public:
		virtual ~vertex_buffer() = default;

		virtual void bind() const = 0;
		virtual void unbind() const = 0;

		virtual void set_data(const void* data, uint32_t size) = 0;
		virtual void set_layout(const buffer_layout& layout) = 0;

		virtual const buffer_layout& get_layout() const = 0;

		static std::shared_ptr<vertex_buffer> create(size_t size);
		static std::shared_ptr<vertex_buffer> create(const float* vertices, size_t size);
	};

	class index_buffer
	{
	public:
		virtual ~index_buffer() = default;

		virtual void bind() const = 0;
		virtual void unbind() const = 0;

		virtual uint32_t get_count() const = 0;
		
		static std::shared_ptr<index_buffer> create(const uint32_t* indices, uint32_t count);
	};

}

#endif
