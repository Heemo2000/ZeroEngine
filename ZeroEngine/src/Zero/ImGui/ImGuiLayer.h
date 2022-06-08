#pragma once
#include "Zero/Core.h"
#include "Zero/Layer.h"


namespace Zero
{
	class ZERO_API ImGuiLayer : public Layer
	{
	private:
		bool m_Show = true;
		float m_Time = 0.0f;
	public:
		ImGuiLayer();
		~ImGuiLayer();

		void OnAttach() override;
		void OnDetach() override;
		void OnUpdate() override;
		void OnEvent(Event& event) override;
		
	};
}


