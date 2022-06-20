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

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender() override;

		void Begin();
		void End();
	};
}


