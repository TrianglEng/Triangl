#include "sandbox2d.hh"

#include "core/log.hh"

#include "render/rendercmd.hh"
#include "render/buffer.hh"

namespace sandbox {

	static std::shared_ptr<triangl::vertex_buffer> s_vbo;
	static std::shared_ptr<triangl::index_buffer>  s_ibo;

	sandbox2d::sandbox2d()
		: triangl::layer("sandbox2d")
	{
	}

	void sandbox2d::on_attach()
	{
		layer::on_attach();

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

		s_vbo = triangl::vertex_buffer::create(vertices, sizeof(vertices));
		s_vbo->set_layout({
			{ triangl::shader_data_type::float3, "a_position" }
		});

		s_ibo = triangl::index_buffer::create(indices, 6);
		s_ibo->bind();
	}

	void sandbox2d::on_event(triangl::event& e)
	{
		layer::on_event(e);
	}

	void sandbox2d::on_update(triangl::timestep ts)
	{
		layer::on_update(ts);
	}

	void sandbox2d::on_render()
	{
		layer::on_render();
	}

	void sandbox2d::on_detach()
	{
		layer::on_detach();

		s_vbo.reset();
		s_ibo.reset();
	}

}
