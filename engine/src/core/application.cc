#include "tlpch.hh"
#include "application.hh"

namespace triangl {

	application::application(const application_spec& spec, const cmdline& args)
		: m_spec(spec), m_args(args)
	{
		TL_CORE_ASSERT(!s_inst, "Another application instance already exists!");

		log::init();
		TL_CORE_INFO("Initialized logging.");

		TL_CORE_INFO("Engine Build Info:");
		TL_CORE_INFO("  Compiled by Compiler: {} ({})", gc_ccinfo.name, gc_ccinfo.abbreviation);
		TL_CORE_INFO("  Compilation at Date: {}", __DATE__);
		TL_CORE_INFO("  Compilation at Time: {}", __TIME__);
	}

	application::~application()
	{
		if (this == s_inst)
		{
			s_inst = nullptr;
		}
	}

	void application::run()
	{
		if (m_running)
		{
			TL_CORE_WARN("application::run() was called, but the application is already running, discarding call...");
			return;
		}

		m_running = true;

		while (m_running)
		{

		}

		cleanup();
	}

	void application::cleanup()
	{

	}

	void application::quit()
	{
		if (!m_running)
		{
			TL_CORE_WARN("application::quit() was called, but the application isn't running, discarding call...");
			return;
		}

		m_running = false;
	}

	void application::exit(int exitcode)
	{
		std::exit(exitcode);
	}

}
