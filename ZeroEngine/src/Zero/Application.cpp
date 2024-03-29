#include "zeropch.h"
#include "Application.h"
#include "Core/Timestep.h"
#include <GLFW/glfw3.h>
#include "Zero/Renderer/Renderer.h"
namespace Zero
{

	
	Application* Application::s_Instance = nullptr;
	
	Application::Application()
	{
		ZERO_CORE_ASSERT(!s_Instance, "Application already exists!");

		s_Instance = this;

		m_Window = Scope<Window>(Window::Create());
		m_Window->SetEventCallback(ZERO_BIND_EVENT_FN(Application::OnEvent));

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);
	}

	Application::~Application()
	{

	}

	void Application::Run()
	{
		while (m_Running)
		{
			float time = glfwGetTime();
			Timestep timestep(time - m_LastDeltaTime);
			m_LastDeltaTime = time;

			if (!m_Minimized)
			{
				for (Layer* layer : m_LayerStack)
				{
					layer->OnUpdate(timestep);
				}

			}
			
			m_ImGuiLayer->Begin();
			for (Layer* layer : m_LayerStack)
			{
				layer->OnImGuiRender();
			}
			m_ImGuiLayer->End();
			
			
			m_Window->OnUpdate();
		}
	}

	void Application::Close()
	{
		m_Running = false;
	}

	void Application::OnEvent(Event& event)
	{
		EventDispatcher dispatcher(event);

		dispatcher.Dispatch<WindowClosedEvent>(ZERO_BIND_EVENT_FN(Application::OnWindowClose));
		dispatcher.Dispatch<WindowResizedEvent>(ZERO_BIND_EVENT_FN(Application::OnWindowResize));
		ZERO_CORE_INFO("{0}", event.ToString());

		for (Layer* layer : m_LayerStack)
		{
			layer->OnEvent(event);
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
		ZERO_CORE_INFO("Deleted {0}", layer->GetLayerName());
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
		ZERO_CORE_INFO("Deleted {0}", overlay->GetLayerName());
		m_LayerStack.PopOverlay(overlay);
		overlay->OnDetach();
	}

	bool Application::OnWindowClose(WindowClosedEvent& event)
	{
		m_Running = false;
		return true;
	}
	bool Application::OnWindowResize(WindowResizedEvent& event)
	{
		if (event.GetWidth() == 0 || event.GetHeight() == 0)
		{
			m_Minimized = true;
			return false;
		}
		m_Minimized = false;
		Renderer::OnWindowResize(event.GetWidth(), event.GetHeight());
		return false;
	}
}
