#include "zeropch.h"
#include "Application.h"
#include <glad/glad.h>
//#include "Events/ApplicationEvent.h"
namespace Zero
{
#define BIND_EVENT_FN(x) std::bind(&Application::x,this,std::placeholders::_1)
	
	Application* Application::s_Instance = nullptr;
	Application::Application()
	{
		ZERO_CORE_ASSERT(!s_Instance, "Application already exists!");

		s_Instance = this;
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
			glClearColor(0, 1, 1, 1);
			glClear(GL_COLOR_BUFFER_BIT);
			
			std::vector<Layer*>::iterator it = m_LayerStack.end();
			while (it != m_LayerStack.begin())
			{
				--it;
				(*it)->OnUpdate();
				//ZERO_CORE_INFO("Calling {0}", (*it)->GetLayerName());
			}
						
			m_Window->OnUpdate();
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
		layer->OnAttach();

		ZERO_CORE_INFO("Added {0}", layer->GetLayerName());
	}

	void Application::PopLayer(Layer* layer)
	{
		m_LayerStack.PopLayer(layer);
		layer->OnDetach();
	}

	void Application::PushOverlay(Layer* overlay)
	{
		m_LayerStack.PushOverlay(overlay);
		overlay->OnAttach();
		ZERO_CORE_INFO("Added {0}", overlay->GetLayerName());
	}

	void Application::PopOverlay(Layer* overlay)
	{
		m_LayerStack.PopOverlay(overlay);
		overlay->OnDetach();
	}

	bool Application::OnWindowClose(WindowClosedEvent& event)
	{
		m_Running = false;
		return true;
	}
}
