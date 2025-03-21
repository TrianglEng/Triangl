#include "sandbox2d.hh"

#include "core/log.hh"

#include "render/vertex_array.hh"
#include "render/rendercmd.hh"

namespace sandbox {

	static std::shared_ptr<triangl::vertex_array>  s_vao;
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

		s_vao = triangl::vertex_array::create();
		s_vao->bind();

		s_vbo = triangl::vertex_buffer::create(vertices, sizeof(vertices));
		s_vbo->set_layout({
			{ triangl::shader_data_type::float3, "a_position" }
		});

		s_ibo = triangl::index_buffer::create(indices, 6);
		s_ibo->bind();

		s_vao->add_vertex_buffer(s_vbo);
		s_vao->set_index_buffer(s_ibo);
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

		triangl::rendercmd::clear();
		triangl::rendercmd::set_clear_color(0.2f, 0.3f, 0.8f, 1.0f);
		triangl::rendercmd::draw_indexed(s_vao);
	}

	void sandbox2d::on_detach()
	{
		layer::on_detach();

		s_vao.reset();
		s_vbo.reset();
		s_ibo.reset();
	}

}
