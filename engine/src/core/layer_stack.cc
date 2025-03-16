#include "tlpch.hh"
#include "layer_stack.hh"

namespace triangl {

	layer_stack::layer_stack()
	{
	}

	layer_stack::layer_stack(std::initializer_list<layer*> layers)
		: m_layers(layers)
	{
	}

	layer_stack::~layer_stack()
	{
		pop_all();
	}

	void layer_stack::push_layer(layer* layer)
	{
		m_layers.emplace(m_layers.begin() + m_layer_index, layer);
		layer->on_attach();
	}

	void layer_stack::push_overlay(layer* overlay)
	{
		m_layers.emplace_back(overlay);
		overlay->on_attach();
	}

	void layer_stack::pop_layer(layer* layer)
	{
		auto end_it = m_layers.begin() + m_layer_index;
		auto it = std::find(m_layers.begin(), end_it, layer);

		if (it != end_it)
		{
			layer->on_detach();
			m_layers.erase(it);
			delete layer;
		}
	}

	void layer_stack::pop_overlay(layer* overlay)
	{
		auto it = std::find(m_layers.begin() + m_layer_index, m_layers.end(), overlay);
		if (it != m_layers.end())
		{
			overlay->on_detach();
			m_layers.erase(it);
			delete overlay;
		}
	}

	void layer_stack::pop_all()
	{
		size_t sz = m_layers.size();
		while (sz--)
		{
			layer* last = m_layers.back();
			last->on_detach();
			delete last;
		}
		m_layers.clear();
	}

}
