#include "zeropch.h"
#include "Application.h"
//#include "Events/ApplicationEvent.h"
namespace Zero
{
#define BIND_EVENT_FN(x) std::bind(&Application::x,this,std::placeholders::_1)
	Application::Application()
	{
		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));
	}

	Application::~Application()
	{
	}

	void Application::Run()
	{
		while (m_Running)
		{
			m_Window->OnUpdate();
			std::vector<Layer*>::iterator it = m_LayerStack.end();
			while (it != m_LayerStack.begin())
			{
				--it;
				(*it)->OnUpdate();
			}
		}
	}

	void Application::OnEvent(Event& event)
	{
		EventDispatcher dispatcher(event);

		dispatcher.Dispatch<WindowClosedEvent>(BIND_EVENT_FN(OnWindowClose));
		ZERO_CORE_INFO("{0}", event.ToString());

		std::vector<Layer*>::iterator it = m_LayerStack.end();
		while (it != m_LayerStack.begin())
		{
			--it;
			(*it)->OnEvent(event);
			if (event.Handled)
			{
				break;
			}
			
		}
	}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
	}

	void Application::PopLayer(Layer* layer)
	{
		m_LayerStack.PopLayer(layer);
	}

	void Application::PushOverlay(Layer* overlay)
	{
		m_LayerStack.PopOverlay(overlay);
	}

	void Application::PopOverlay(Layer* overlay)
	{
		m_LayerStack.PopOverlay(overlay);
	}

	bool Application::OnWindowClose(WindowClosedEvent& event)
	{
		m_Running = false;
		return true;
	}
}
