#include "sandbox2d.hh"

#include "core/log.hh"

namespace sandbox {

	sandbox2d::sandbox2d()
		: triangl::layer("sandbox2d")
	{
	}

	void sandbox2d::on_attach()
	{
		layer::on_attach();
		TL_INFO("sandbox2d::on_attach()");
	}

	void sandbox2d::on_event(triangl::event& e)
	{
		layer::on_event(e);
		TL_INFO("sandbox2d::on_event({})", e);
	}

	void sandbox2d::on_update(triangl::timestep ts)
	{
		layer::on_update(ts);
		//TL_INFO("sandbox2d::on_update({})", ts);
	}

	void sandbox2d::on_render()
	{
		layer::on_render();
		//TL_INFO("sandbox2d::on_render()");
	}

	void sandbox2d::on_detach()
	{
		layer::on_detach();
		TL_INFO("sandbox2d::on_detach()");
	}

}
