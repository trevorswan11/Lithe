#pragma once

#include  "Lithe/Core.h"
#include "Layer.h"

#include <vector>

namespace Lithe {

	// LayerStack is owned by the applcaiton, layers should live for a long long time

	class LITHE_API LayerStack
	{
	using layer_stack = std::vector<Layer*>;
	public:
		LayerStack();
		~LayerStack();

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);
		void PopLayer(Layer* layer);
		void PopOverlay(Layer* overlay);

		layer_stack::iterator begin() { return m_Layers.begin(); }
		layer_stack::iterator end() { return m_Layers.end(); }
		layer_stack::reverse_iterator rbegin() { return m_Layers.rbegin(); }
		layer_stack::reverse_iterator rend() { return m_Layers.rend(); }

		layer_stack::const_iterator begin() const { return m_Layers.begin(); }
		layer_stack::const_iterator end()	const { return m_Layers.end(); }
		layer_stack::const_reverse_iterator rbegin() const { return m_Layers.rbegin(); }
		layer_stack::const_reverse_iterator rend() const { return m_Layers.rend(); }
	private:
		layer_stack m_Layers;
		layer_stack::iterator m_LayerInsert;
	};
}

