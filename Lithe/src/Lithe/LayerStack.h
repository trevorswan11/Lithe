#pragma once

#include "Lithe/Base.h"
#include "Lithe/Layer.h"

#include <vector>

namespace Lithe {

	// LayerStack is 2owned by the applcaiton, layers should live for a long long time

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
	private:
		layer_stack m_Layers;
		unsigned int m_LayerInsertIndex = 0;
	};

}

