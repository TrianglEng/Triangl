#ifndef SANDBOX_SANDBOX2D_HH
#define SANDBOX_SANDBOX2D_HH 1

#include "core/layer.hh"

namespace sandbox {

	class sandbox2d : public triangl::layer
	{
	public:
		sandbox2d();

		virtual void on_attach() override;
		virtual void on_event(triangl::event& e) override;
		virtual void on_update(triangl::timestep ts) override;
		virtual void on_render() override;
		virtual void on_detach() override;
	};

}

#endif
