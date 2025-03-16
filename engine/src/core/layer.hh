#ifndef TRIANGL_CORE_LAYER_HH
#define TRIANGL_CORE_LAYER_HH

#include "event/event.hh"
#include "misc/timestep.hh"

namespace triangl {

	class layer
	{
	public:
		layer(std::string_view name);
		virtual ~layer() = default;

		virtual void on_attach() {}
		virtual void on_event(event& e) {}
		virtual void on_update(timestep ts) {}
		virtual void on_render() {}
		virtual void on_detach() {}

		const std::string& get_name() const { return m_name; }
	private:
		std::string m_name;
	};

}

#endif
