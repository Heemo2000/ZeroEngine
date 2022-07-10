#include "zeropch.h"
#include "Application.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
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
		
		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);

		float vertices[] =
		{
			-0.5f,-0.5f,0.0f, 0.0f,0.0f,0.0f,1.0f,
			0.5f,-0.5f,0.0f,  1.0f,0.0f,0.0f,1.0f,
			0.0f,0.5f,0.0f,   0.5f,0.5f,0.0f,1.0f
		};

		unsigned int indices[1 * 3] =
		{
			0,1,2
		};

		BufferLayout layout = 
		  { 
			{"a_Position",ShaderDataType::Float3},
			{"a_Color",ShaderDataType::Float4}
		  };

		m_VertexArray.reset(VertexArray::Create());
		m_VertexArray->Bind();
		
		m_VertexBuffer.reset(VertexBuffer::Create(vertices,sizeof(vertices)));
		m_VertexBuffer->SetLayout(layout);

		m_IndexBuffer.reset(IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));

		m_VertexArray->AddVertexBuffer(m_VertexBuffer);
		m_VertexArray->SetIndexBuffer(m_IndexBuffer);

		m_VertexArray->Unbind();
		m_IndexBuffer->Unbind();
		m_VertexBuffer->Unbind();		
		
		std::string vertexSource = R"(
			#version 460 core
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;
			out vec4 v_Color;
		    void main()
			{				
				v_Color = a_Color;
				gl_Position = vec4(a_Position,1.0);
			}
		)";
		
		std::string fragmentSource = R"(
			#version 460 core
			in vec4 v_Color;
			out vec4 outColor;
		    void main()
			{
				outColor = v_Color;
			}
		)";

		m_Shader.reset(Shader::Create(vertexSource,fragmentSource));
		m_Shader->Bind();
	}

	Application::~Application()
	{

	}

	void Application::Run()
	{
		while (m_Running)
		{
			glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);

			m_VertexArray->Bind();
			glDrawElements(GL_TRIANGLES, m_VertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, (void*)0);

			for (Layer* layer : m_LayerStack)
			{
				layer->OnUpdate();
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

	void Application::OnEvent(Event& event)
	{
		EventDispatcher dispatcher(event);

		dispatcher.Dispatch<WindowClosedEvent>(BIND_EVENT_FN(OnWindowClose));
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
}
