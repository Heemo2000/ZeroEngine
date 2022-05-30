#include "Core.h"
#include "Events/Event.h"
#include "Events/ApplicationEvent.h"
#include "Events/EventDispatcher.h"
#include "Window.h"
#include "LayerStack.h"
#include "Layer.h"
namespace Zero
{
	class ZERO_API Application
	{
	public:
		Application();
		virtual ~Application();
		void Run();
		void OnEvent(Event& event);
		void PushLayer(Layer* layer);
		void PopLayer(Layer* layer);
		void PushOverlay(Layer* overlay);
		void PopOverlay(Layer* overlay);

	private:
		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
		bool OnWindowClose(WindowClosedEvent& event);
		LayerStack m_LayerStack;
	};

	//To be defined in client.
	Application* CreateApplication();
}


