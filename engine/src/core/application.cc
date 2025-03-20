#include "tlpch.hh"
#include "application.hh"

#include "input/input.hh"
#include "render/rendercmd.hh"
#include "util/platformutil.hh"

namespace triangl {

	application::application(const application_spec& spec, const cmdline& args)
		: m_spec(spec), m_args(args)
	{
		TL_CORE_ASSERT(!s_inst, "another application instance already exists!");
		s_inst = this;

		log::init();
		TL_CORE_INFO("initialized logging.");

		TL_CORE_INFO("engine build info:");
		TL_CORE_INFO("  compiled by compiler: {} ({})", gc_ccinfo.name, gc_ccinfo.abbreviation);
		TL_CORE_INFO("  compilation at date: {}", __DATE__);
		TL_CORE_INFO("  compilation at time: {}", __TIME__);
		TL_CORE_INFO("  build configuration: {}", build_config_to_string(gc_buildcfg));
		TL_CORE_INFO("  platform: {} ({})", platform_to_string(gc_platform), architecture_to_string(gc_arch));

		m_window = window::create(m_spec.main_window_props);
		if (!m_window || !m_window->init())
		{
			TL_CORE_FATAL("main application window creation failure!");
		}
		m_window->set_event_callback(TL_BIND_METHOD(this, application::on_event));

		input::init();
		rendercmd::init();
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
			float time = platform_util::get_time();
			timestep ts = time - m_last_frame_time;
			m_last_frame_time = time;

			for (layer* l : m_layer_stack)
			{
				l->on_update(ts);
			}

			for (layer* l : m_layer_stack)
			{
				l->on_render();
			}

			m_window->update();
		}

		cleanup();
	}

	void application::cleanup()
	{
		m_layer_stack.pop_all();

		if (m_window->is_open())
		{
			m_window->destroy();
		}
	}

	void application::on_event(event& e)
	{
		event_dispatcher dispatcher(e);
		dispatcher.dispatch<window_closed_event>(TL_BIND_METHOD(this, application::on_window_closed));
		dispatcher.dispatch<window_resized_event>(TL_BIND_METHOD(this, application::on_window_resized));

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
