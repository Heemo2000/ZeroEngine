#pragma once
#include "Zero/Core.h"
#include "Zero/Layer.h"

#include "Zero/Window.h"

namespace Zero
{
	class ZERO_API ImGuiLayer : public Layer
	{

	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender() override;
		virtual void OnEvent(Event& event) override;

		void Begin();
		void End();

	private:
		float m_Time = 0.0f;
		Window* m_Window;
		bool m_BlockEvents = true;
	};
}


