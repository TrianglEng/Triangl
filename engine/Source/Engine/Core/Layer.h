#pragma once

#include "Event/Event.h"
#include "Misc/Timestep.h"

#include <string>

namespace Triangl
{
	class Layer
	{
	public:
		Layer(std::string_view name);
		virtual ~Layer() = default;

		virtual void OnAttach() {}
		virtual void OnEvent(Event& e) {}
		virtual void OnUpdate(Timestep ts) {}
		virtual void OnRender() {}
		virtual void OnDetach() {}

		const std::string& GetName() const { return m_Name; }
	private:
		std::string m_Name;
	};
}
