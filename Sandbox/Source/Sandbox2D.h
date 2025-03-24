#pragma once

#include "Core/Layer.h"

namespace Sandbox
{
	class Sandbox2D : public Triangl::Layer
	{
	public:
		Sandbox2D();

		virtual void OnAttach() override;
		virtual void OnEvent(Triangl::Event& e) override;
		virtual void OnUpdate(Triangl::Timestep ts) override;
		virtual void OnRender() override;
		virtual void OnDetach() override;
	};
}
