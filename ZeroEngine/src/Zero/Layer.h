#pragma once
#include "zeropch.h"
#include "Core.h"
#include "Events/Event.h"


namespace Zero
{
	class ZERO_API Layer
	{
	private:
		std::string m_LayerName;
	public:
		Layer(const std::string& layerName = "Layer") : m_LayerName(layerName) {}
		virtual ~Layer() {}
		virtual void OnUpdate() {}
		virtual void OnEvent(Event& event) {}
		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnImGuiRender() {}
		inline const std::string GetLayerName() const { return m_LayerName; }
	};
}
