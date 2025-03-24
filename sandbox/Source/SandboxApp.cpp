#include "SandboxApp.h"

// >> Entry Point Declared & Implemented Here <<
#include "Core/EntryPoint.h"
// >> Entry Point Declared & Implemented Here <<

// Layers
#include "Sandbox2D.h"

namespace Sandbox
{
	SandboxApp::SandboxApp(const Triangl::ApplicationSpecification& specification, const Triangl::CommandLine& args)
		: Triangl::Application(specification, args)
	{
		PushLayer(new Sandbox2D());
	}

	SandboxApp::~SandboxApp()
	{
	}
}

Triangl::Application* Triangl::CreateApplication(const Triangl::CommandLine& args)
{
	Triangl::ApplicationSpecification specification;

	specification.Name = "Sandbox";
	specification.MainWindowProps.Title = specification.Name;

	return new Sandbox::SandboxApp(specification, args);
}
