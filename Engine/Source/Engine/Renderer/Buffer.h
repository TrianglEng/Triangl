#pragma once

#include "Core/Base.h"

namespace Triangl
{
	enum class ShaderDataType
	{
		None = 0,
		Float, Float2, Float3, Float4,
		Mat3, Mat4,
		Int1, Int2, Int3, Int4,
		Bool
	};

	size_t SizeOfShaderDataType(ShaderDataType type);

	struct BufferElement
	{
		std::string Name;
		ShaderDataType Type = ShaderDataType::None;
		size_t Size = 0, Offset = 0;
		bool Normalized = false;

		BufferElement(ShaderDataType type, std::string_view name, bool normalized = false)
			: Name(name), Type(type), Size(SizeOfShaderDataType(type)), Offset(0), Normalized(normalized) {}

		uint8_t GetComponentCount() const;
	};

	class BufferLayout
	{
	public:
		BufferLayout() = default;
		BufferLayout(std::initializer_list<BufferElement> elements)
			: m_Elements(elements)
		{
			CalculateElementOffsetsAndStride();
		}

		std::vector<BufferElement>::iterator begin() { return m_Elements.begin(); }
		std::vector<BufferElement>::iterator end() { return m_Elements.end(); }
		std::vector<BufferElement>::const_iterator begin() const { return m_Elements.begin(); }
		std::vector<BufferElement>::const_iterator end() const { return m_Elements.end(); }
		std::vector<BufferElement>::const_iterator cbegin() const { return m_Elements.begin(); }
		std::vector<BufferElement>::const_iterator cend() const { return m_Elements.end(); }
		std::vector<BufferElement>::reverse_iterator rbegin() { return m_Elements.rbegin(); }
		std::vector<BufferElement>::reverse_iterator rend() { return m_Elements.rend(); }
		std::vector<BufferElement>::const_reverse_iterator rbegin() const { return m_Elements.rbegin(); }
		std::vector<BufferElement>::const_reverse_iterator rend() const { return m_Elements.rend(); }
		std::vector<BufferElement>::const_reverse_iterator crbegin() const { return m_Elements.crbegin(); }
		std::vector<BufferElement>::const_reverse_iterator crend() const { return m_Elements.crend(); }

		const std::vector<BufferElement>& GetElements() const { return m_Elements; }
		size_t GetStride() const { return m_Stride; }
	private:
		void CalculateElementOffsetsAndStride()
		{
			m_Stride = 0;
			for (BufferElement& element : m_Elements)
			{
				element.Offset = m_Stride;
				m_Stride += element.Size;
			}
		}
	private:
		std::vector<BufferElement> m_Elements;
		size_t m_Stride = 0;
	};

	class VertexBuffer
	{
	public:
		virtual ~VertexBuffer() = default;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void SetData(const void* data, uint32_t size) = 0;
		virtual void SetLayout(const BufferLayout& layout) = 0;

		virtual const BufferLayout& GetLayout() const = 0;

		static Ref<VertexBuffer> New(size_t size);
		static Ref<VertexBuffer> New(const float* vertices, size_t size);
	};

	class IndexBuffer
	{
	public:
		virtual ~IndexBuffer() = default;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual uint32_t GetCount() const = 0;
		
		static std::shared_ptr<IndexBuffer> New(const uint32_t* indices, uint32_t count);
	};
}
