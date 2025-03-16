#ifndef TRIANGL_CORE_LAYER_STACK_HH
#define TRIANGL_CORE_LAYER_STACK_HH

#include "core/layer.hh"

namespace triangl {

	class layer_stack
	{
	public:
		layer_stack();
		layer_stack(std::initializer_list<layer*> layers);
		~layer_stack();

		void push_layer(layer* layer);
		void push_overlay(layer* overlay);
		void pop_layer(layer* layer);
		void pop_overlay(layer* overlay);
		void pop_all();

		std::vector<layer*>::iterator begin() { return m_layers.begin(); }
		std::vector<layer*>::iterator end() { return m_layers.end(); }
		std::vector<layer*>::const_iterator begin() const { return m_layers.begin(); }
		std::vector<layer*>::const_iterator end() const { return m_layers.end(); }
		std::vector<layer*>::const_iterator cbegin() const { return m_layers.begin(); }
		std::vector<layer*>::const_iterator cend() const { return m_layers.end(); }
		std::vector<layer*>::reverse_iterator rbegin() { return m_layers.rbegin(); }
		std::vector<layer*>::reverse_iterator rend() { return m_layers.rend(); }
		std::vector<layer*>::const_reverse_iterator rbegin() const { return m_layers.rbegin(); }
		std::vector<layer*>::const_reverse_iterator rend() const { return m_layers.rend(); }
		std::vector<layer*>::const_reverse_iterator crbegin() const { return m_layers.crbegin(); }
		std::vector<layer*>::const_reverse_iterator crend() const { return m_layers.crend(); }

		const std::vector<layer*>& get_layers() const { return m_layers; }
	private:
		std::vector<layer*> m_layers;
		size_t m_layer_index = 0;
	};

}

#endif
