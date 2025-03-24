#pragma once

#include "Core/Application.h"

namespace Sandbox
{
	class SandboxApp : public Triangl::Application
	{
	public:
		SandboxApp(const Triangl::ApplicationSpecification& specification, const Triangl::CommandLine& args);
		virtual ~SandboxApp() override;
	};
}
