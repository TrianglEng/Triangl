#include "Sandbox2D.h"

#include "Core/Log.h"

#include "Renderer/RenderCommand.h"
#include "Renderer/VertexArray.h"

namespace Sandbox
{
	static Triangl::Ref<Triangl::VertexArray>  s_VertexArray;
	static Triangl::Ref<Triangl::VertexBuffer> s_VertexBuffer;
	static Triangl::Ref<Triangl::IndexBuffer>  s_IndexBuffer;

	Sandbox2D::Sandbox2D()
		: Triangl::Layer("Sandbox2D")
	{
	}

	void Sandbox2D::OnAttach()
	{
		float vertices[] =
		{
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			-0.5f,  0.5f, 0.0f,
			 0.5f,  0.5f, 0.0f
		};

		uint32_t indices[] =
		{
			0, 1, 2,
			1, 2, 3
		};

		s_VertexArray = Triangl::VertexArray::New();
		s_VertexArray->Bind();

		s_VertexBuffer = Triangl::VertexBuffer::New(vertices, sizeof(vertices));
		s_VertexBuffer->SetLayout({
			{ Triangl::ShaderDataType::Float3, "a_Position" }
		});

		s_IndexBuffer = Triangl::IndexBuffer::New(indices, 6);
		s_IndexBuffer->Bind();

		s_VertexArray->AddVertexBuffer(s_VertexBuffer);
		s_VertexArray->SetIndexBuffer(s_IndexBuffer);
	}

	void Sandbox2D::OnEvent(Triangl::Event& e)
	{
	}

	void Sandbox2D::OnUpdate(Triangl::Timestep ts)
	{
	}

	void Sandbox2D::OnRender()
	{
		Triangl::RenderCommand::Clear();
		Triangl::RenderCommand::SetClearColor(0.2f, 0.3f, 0.8f, 1.0f);
		Triangl::RenderCommand::DrawIndexed(s_VertexArray);
	}

	void Sandbox2D::OnDetach()
	{
		s_VertexArray.reset();
		s_VertexBuffer.reset();
		s_IndexBuffer.reset();
	}
}
