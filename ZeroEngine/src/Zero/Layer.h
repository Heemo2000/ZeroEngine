#pragma once
#include "zeropch.h"
#include "Core.h"
#include "Events/Event.h"
#include "Core/Timestep.h"

namespace Zero
{
	class ZERO_API Layer
	{
	public:
		Layer(const std::string& layerName = "Layer") : m_LayerName(layerName) {}
		virtual ~Layer() {}
		virtual void OnUpdate(Timestep timestep) {}
		virtual void OnEvent(Event& event) {}
		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnImGuiRender() {}
		inline const std::string GetLayerName() const { return m_LayerName; }
	private:
		std::string m_LayerName;
	
	};
}
