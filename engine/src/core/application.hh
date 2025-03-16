#ifndef TRIANGL_CORE_APPLICATION_HH
#define TRIANGL_CORE_APPLICATION_HH 1

#include "core/layer_stack.hh"
#include "event/app_event.hh"
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

		void push_layer(layer* layer);
		void push_overlay(layer* overlay);
		void pop_layer(layer* layer);
		void pop_overlay(layer* overlay);

		const application_spec& get_spec() const { return m_spec; }
		const cmdline& get_args() const { return m_args; }

		const layer_stack& get_layer_stack() const { return m_layer_stack; }
		bool is_running() const { return m_running; }

		static application* inst() { return s_inst; }
	private:
		void cleanup();

		void on_event(event& e);
		bool on_window_closed(window_closed_event& e);
		bool on_window_resized(window_resized_event& e);
	private:
		application_spec m_spec;
		cmdline m_args;

		layer_stack m_layer_stack;
		bool m_running = false;
	private:
		inline static application* s_inst = nullptr;
	};

	application* create_application_instance(const cmdline& args);

}

#endif TRIANGL_CORE_APPLICATION_HH
