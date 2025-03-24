#include "TrianglPCH.h"
#include "Buffer.h"

#include "Renderer/RendererAPI.h"
#include "Platform/OpenGL/OpenGLBuffer.h"

namespace Triangl
{
	size_t SizeOfShaderDataType(ShaderDataType type)
	{
		switch (type)
		{
		case ShaderDataType::Float:   return 4;
		case ShaderDataType::Float2:  return 4 * 2;
		case ShaderDataType::Float3:  return 4 * 3;
		case ShaderDataType::Float4:  return 4 * 4;
		case ShaderDataType::Mat3:    return 4 * 3 * 3;
		case ShaderDataType::Mat4:    return 4 * 4 * 4;
		case ShaderDataType::Int1:    return 4;
		case ShaderDataType::Int2:    return 4 * 2;
		case ShaderDataType::Int3:    return 4 * 3;
		case ShaderDataType::Int4:    return 4 * 4;
		case ShaderDataType::Bool:    return 1;
		}

		TL_CORE_ASSERT(false, "Unknown ShaderDataType!");
		return 0;
	}

	uint8_t BufferElement::GetComponentCount() const
	{
		switch (Type)
		{
		case ShaderDataType::Float:   return 1;
		case ShaderDataType::Float2:  return 2;
		case ShaderDataType::Float3:  return 3;
		case ShaderDataType::Float4:  return 4;
		case ShaderDataType::Mat3:    return 3;
		case ShaderDataType::Mat4:    return 4;
		case ShaderDataType::Int1:    return 1;
		case ShaderDataType::Int2:    return 2;
		case ShaderDataType::Int3:    return 3;
		case ShaderDataType::Int4:    return 4;
		case ShaderDataType::Bool:    return 1;
		}

		TL_CORE_ASSERT(false, "Unknown ShaderDataType!");
		return 0;
	}

	Ref<VertexBuffer> VertexBuffer::New(size_t size)
	{
		switch (RendererAPI::GetAPI())
		{
		case GraphicsAPI::OpenGL: return MakeRef<OpenGLVertexBuffer>(size);
		default: break;
		}

		TL_CORE_ASSERT(false, "Unknown GraphicsAPI!");
		return nullptr;
	}

	Ref<VertexBuffer> VertexBuffer::New(const float* vertices, size_t size)
	{
		switch (RendererAPI::GetAPI())
		{
		case GraphicsAPI::OpenGL: return MakeRef<OpenGLVertexBuffer>(vertices, size);
		default: break;
		}

		TL_CORE_ASSERT(false, "Unknown GraphicsAPI!");
		return nullptr;
	}

	Ref<IndexBuffer> IndexBuffer::New(const uint32_t* indices, uint32_t count)
	{
		switch (RendererAPI::GetAPI())
		{
		case GraphicsAPI::OpenGL: return MakeRef<OpenGLIndexBuffer>(indices, count);
		default: break;
		}

		TL_CORE_ASSERT(false, "Unknown GraphicsAPI!");
		return nullptr;
	}
}
