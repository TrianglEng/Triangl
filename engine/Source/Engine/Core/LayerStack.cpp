#include "TrianglPCH.h"
#include "LayerStack.h"

namespace Triangl
{
	LayerStack::LayerStack()
	{
	}

	LayerStack::LayerStack(std::initializer_list<Layer*> layers)
		: m_Layers(layers)
	{
		for (Layer* layer : layers)
		{
			layer->OnAttach();
		}
	}

	LayerStack::~LayerStack()
	{
		PopAll();
	}

	void LayerStack::PushLayer(Layer* layer)
	{
		m_Layers.emplace(m_Layers.begin() + m_LayerInsertIndex, layer);
		layer->OnAttach();
	}

	void LayerStack::PushOverlay(Layer* overlay)
	{
		m_Layers.emplace_back(overlay);
		overlay->OnAttach();
	}

	void LayerStack::PopLayer(Layer* layer)
	{
		auto endIt = m_Layers.begin() + m_LayerInsertIndex;
		auto it = std::find(m_Layers.begin(), endIt, layer);

		if (it != endIt)
		{
			layer->OnDetach();
			m_Layers.erase(it);
			delete layer;
		}
	}

	void LayerStack::PopOverlay(Layer* overlay)
	{
		auto it = std::find(m_Layers.begin() + m_LayerInsertIndex, m_Layers.end(), overlay);
		if (it != m_Layers.end())
		{
			overlay->OnDetach();
			m_Layers.erase(it);
			delete overlay;
		}
	}

	void LayerStack::PopAll()
	{
		size_t size = m_Layers.size();
		while (size--)
		{
			Layer* last = m_Layers.back();
			last->GetName();
			delete last;
		}
		m_Layers.clear();
	}
}
