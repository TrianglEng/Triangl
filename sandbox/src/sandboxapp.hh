#ifndef SANDBOX_SANDBOXAPP_HH
#define SANDBOX_SANDBOXAPP_HH 1

#include "core/application.hh"

namespace sandbox {

	class sandbox_application : public triangl::application
	{
	public:
		sandbox_application(const triangl::application_spec& spec, const triangl::cmdline& args);
		virtual ~sandbox_application() override;
	};

}

#endif
