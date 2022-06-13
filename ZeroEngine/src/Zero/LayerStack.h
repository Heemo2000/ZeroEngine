#pragma once
#include "Core.h"
#include "Layer.h"

namespace Zero
{
	class ZERO_API LayerStack
	{
	private:
		std::vector<Layer*> m_Layers;
	public:
		LayerStack();
		~LayerStack();
		void PushLayer(Layer* layer);
		void PopLayer(Layer* layer);
		void PushOverlay(Layer* overlay);
		void PopOverlay(Layer* overlay);

		std::vector<Layer*>::iterator begin() { return m_Layers.begin(); }
		std::vector<Layer*>::iterator end() { return m_Layers.end(); }
	};
}

