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
			// TODO: actually calculate the timestep between this and the last frame
			timestep ts = 0.0f;

			for (layer* l : m_layer_stack)
			{
				l->on_update(ts);
			}

			for (layer* l : m_layer_stack)
			{
				l->on_render();
			}
		}

		cleanup();
	}

	void application::cleanup()
	{
		m_layer_stack.pop_all();
	}

	void application::on_event(event& e)
	{
		event_dispatcher dispatcher(e);
		dispatcher.dispatch<window_closed_event>(TL_BIND_METHOD_ON_OBJECT(this, application::on_window_closed));
		dispatcher.dispatch<window_resized_event>(TL_BIND_METHOD_ON_OBJECT(this, application::on_window_resized));

		for (auto it = m_layer_stack.rbegin(); it != m_layer_stack.rend(); ++it)
		{
			if (e.handled)
			{
				break;
			}

			(*it)->on_event(e);
		}
	}

	bool application::on_window_closed(window_closed_event& e)
	{
		TL_CORE_TRACE("application instance received window_closed_event, sending quit request");

		quit();
		return true; // event handled
	}

	bool application::on_window_resized(window_resized_event& e)
	{
		// TODO: report to renderer
		return false; // event not handled
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

	void application::push_layer(layer* layer)
	{
		m_layer_stack.push_layer(layer);
	}

	void application::push_overlay(layer* overlay)
	{
		m_layer_stack.push_overlay(overlay);
	}

	void application::pop_layer(layer* layer)
	{
		m_layer_stack.pop_layer(layer);
	}

	void application::pop_overlay(layer* overlay)
	{
		m_layer_stack.pop_overlay(overlay);
	}

}
