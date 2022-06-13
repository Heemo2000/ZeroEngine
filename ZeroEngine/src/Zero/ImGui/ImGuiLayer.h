#pragma once
#include "Zero/Core.h"
#include "Zero/Layer.h"
#include "Zero/Events/EventDispatcher.h"
#include "Zero/Events/ApplicationEvent.h"
#include "Zero/Events/KeyEvent.h"
#include "Zero/Events/MouseButtonEvent.h"
#include "Zero/Events/MouseMovedEvent.h"
#include "Zero/Events/MouseScrolledEvent.h"



namespace Zero
{
	class ZERO_API ImGuiLayer : public Layer
	{
	private:
		bool m_Show = true;
		float m_Time = 0.0f;

	private:
		bool OnWindowResized(WindowResizedEvent& event);
		bool OnKeyPressed(KeyPressedEvent& event);
		bool OnKeyReleased(KeyReleasedEvent& event);
		bool OnKeyTyped(KeyTypedEvent& event);
		bool OnMouseMoved(MouseMovedEvent& event);
		bool OnMouseButtonClicked(MouseButtonClickedEvent& event);
		bool OnMouseButtonReleased(MouseButtonReleasedEvent& event);
		bool OnMouseScrolled(MouseScrolledEvent& event);


	public:
		ImGuiLayer();
		~ImGuiLayer();

		void OnAttach() override;
		void OnDetach() override;
		void OnUpdate() override;
		void OnEvent(Event& event) override;
		
		
	};
}


