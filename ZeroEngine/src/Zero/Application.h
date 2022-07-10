#include "Core.h"
#include "Events/Event.h"
#include "Events/ApplicationEvent.h"
#include "Events/EventDispatcher.h"
#include "Window.h"
#include "LayerStack.h"
#include "Layer.h"
#include "ImGui/ImGuiLayer.h"

#include "Renderer/Shader.h"
#include "Renderer/Buffer.h"
#include "Renderer/VertexArray.h"

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
	public:
		inline static Application& GetInstance() { return *s_Instance; }
		inline Window* GetWindow() { return m_Window.get(); }

	private:
		static Application* s_Instance;

	private:
		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		bool OnWindowClose(WindowClosedEvent& event);
		LayerStack m_LayerStack;
		std::unique_ptr<VertexArray> m_VertexArray;
		std::shared_ptr<VertexBuffer> m_VertexBuffer;
		std::shared_ptr<IndexBuffer> m_IndexBuffer;
		std::unique_ptr<Shader> m_Shader;
	};

	//To be defined in client.
	Application* CreateApplication();
}


