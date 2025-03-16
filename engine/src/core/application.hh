#ifndef TRIANGL_CORE_APPLICATION_HH
#define TRIANGL_CORE_APPLICATION_HH 1

#include "core/base.hh"
#include "misc/cmdline.hh"

namespace triangl {

	struct application_spec
	{
		std::string name = "Triangl Application";
		std::string wdir;
	};

	class application
	{
	public:
		application(const application_spec& spec, const cmdline& args);
		virtual ~application();

		void run();
		void quit();
		[[noreturn]] void exit(int exitcode);

		const application_spec& get_spec() const { return m_spec; }
		const cmdline& get_args() const { return m_args; }

		bool is_running() const { return m_running; }

		static application* inst() { return s_inst; }
	private:
		void cleanup();
	private:
		application_spec m_spec;
		cmdline m_args;

		bool m_running = false;
	private:
		inline static application* s_inst = nullptr;
	};

	application* create_application_instance(const cmdline& args);

}

#endif TRIANGL_CORE_APPLICATION_HH
