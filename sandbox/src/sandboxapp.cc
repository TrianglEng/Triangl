#include "sandboxapp.hh"

// main defined here
#include "core/entry_point.hh"

namespace sandbox {

	sandbox_application::sandbox_application(const triangl::application_spec& spec, const triangl::cmdline& args)
		: application(spec, args)
	{
		
	}

	sandbox_application::~sandbox_application()
	{
	}

}

triangl::application* triangl::create_application_instance(const triangl::cmdline& args)
{
	triangl::application_spec spec;
	spec.name = "Sandbox";

	return new sandbox::sandbox_application(spec, args);
}
