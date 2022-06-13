#include "zeropch.h"

#include "ImGuiLayer.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "imgui.h"

#include "Platform/OpenGL/ImGuiOpenGLRenderer.h"
#include "Platform/OpenGL/imgui_impl_glfw.h"

#include "Zero/Application.h"
#include "Platform/Windows/WindowsWindow.h"


namespace Zero
{
	ImGuiLayer::ImGuiLayer() : Layer("ImGuiLayer")
	{

	}

	ImGuiLayer::~ImGuiLayer()
	{
	}

	void ImGuiLayer::OnAttach()
	{
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGui::StyleColorsDark();

		ImGuiIO& io = ImGui::GetIO();
		io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
		io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;

		
		Application& app = Application::GetInstance();
		Window* window = app.GetWindow();

		WindowsWindow* windowsWindow = dynamic_cast<WindowsWindow*>(window);
		ImGui_ImplGlfw_InitForOpenGL(windowsWindow->GetGLFWwindow(), true);
		ImGui_ImplOpenGL3_Init("#version 460 core");



	}

	void ImGuiLayer::OnDetach()
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui::DestroyContext();
	}

	void ImGuiLayer::OnUpdate()
	{
		ImGuiIO& io = ImGui::GetIO();

		Application& app = Application::GetInstance();
		Window* window = app.GetWindow();
		io.DisplaySize = ImVec2(window->GetWidth(), window->GetHeight());

		float time = (float)glfwGetTime();
		io.DeltaTime = (m_Time > 0.0f) ? (time - m_Time) : (1.0f / 60.0f);
		m_Time = time;

		//ZERO_CORE_INFO("ImGui is working");
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		ImGui::ShowDemoWindow(&m_Show);

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}

	void ImGuiLayer::OnEvent(Event& event)
	{
		EventDispatcher dispatcher(event);

		dispatcher.Dispatch<WindowResizedEvent>(ZERO_BIND_EVENT_FN(ImGuiLayer::OnWindowResized));
		dispatcher.Dispatch<KeyPressedEvent>(ZERO_BIND_EVENT_FN(ImGuiLayer::OnKeyPressed));
		dispatcher.Dispatch<KeyReleasedEvent>(ZERO_BIND_EVENT_FN(ImGuiLayer::OnKeyReleased));
		//dispatcher.Dispatch<KeyTypedEvent>(ZERO_BIND_EVENT_FN(ImGuiLayer::OnKeyTyped));
		dispatcher.Dispatch<MouseMovedEvent>(ZERO_BIND_EVENT_FN(ImGuiLayer::OnMouseMoved));
		dispatcher.Dispatch<MouseButtonClickedEvent>(ZERO_BIND_EVENT_FN(ImGuiLayer::OnMouseButtonClicked));
		dispatcher.Dispatch<MouseButtonReleasedEvent>(ZERO_BIND_EVENT_FN(ImGuiLayer::OnMouseButtonReleased));
		dispatcher.Dispatch<MouseScrolledEvent>(ZERO_BIND_EVENT_FN(ImGuiLayer::OnMouseScrolled));
	}

	bool ImGuiLayer::OnWindowResized(WindowResizedEvent& event)
	{
		ImGuiIO& io = ImGui::GetIO();

		io.DisplaySize = ImVec2(event.GetWidth(), event.GetHeight());
		io.DisplayFramebufferScale = ImVec2(1.0f, 1.0f);
		glViewport(0, 0, event.GetWidth(), event.GetHeight());
		return true;
	}

	bool ImGuiLayer::OnKeyPressed(KeyPressedEvent& event)
	{
		ImGuiIO& io = ImGui::GetIO();

		io.KeysDown[event.GetKeyCode()] = true;
		
		io.KeyCtrl = io.KeysDown[GLFW_KEY_LEFT_CONTROL] || io.KeysDown[GLFW_KEY_RIGHT_CONTROL];
		io.KeyAlt = io.KeysDown[GLFW_KEY_LEFT_ALT] || io.KeysDown[GLFW_KEY_RIGHT_ALT];
		io.KeyShift = io.KeysDown[GLFW_KEY_LEFT_SHIFT] || io.KeysDown[GLFW_KEY_RIGHT_SHIFT];
		io.KeySuper = io.KeysDown[GLFW_KEY_LEFT_SUPER] || io.KeysDown[GLFW_KEY_RIGHT_SUPER];
		return true;
	}

	bool ImGuiLayer::OnKeyReleased(KeyReleasedEvent& event)
	{
		ImGuiIO& io = ImGui::GetIO();

		io.KeysDown[event.GetKeyCode()] = false;
		return true;
	}

	bool ImGuiLayer::OnKeyTyped(KeyTypedEvent& event)
	{
		ImGuiIO& io = ImGui::GetIO();
		
		io.AddInputCharacter((unsigned int)event.GetKeyCode());
		return true;
	}

	bool ImGuiLayer::OnMouseMoved(MouseMovedEvent& event)
	{
		ImGuiIO& io = ImGui::GetIO();

		io.MousePos = ImVec2(event.GetMouseX(), event.GetMouseY());
		return true;
	}

	bool ImGuiLayer::OnMouseButtonClicked(MouseButtonClickedEvent& event)
	{
		ImGuiIO& io = ImGui::GetIO();

		io.MouseClicked[event.GetMouseButton()] = true;
		return true;
	}

	bool ImGuiLayer::OnMouseButtonReleased(MouseButtonReleasedEvent& event)
	{
		ImGuiIO& io = ImGui::GetIO();

		io.MouseReleased[event.GetMouseButton()] = true;
		return true;
	}

	bool ImGuiLayer::OnMouseScrolled(MouseScrolledEvent& event)
	{
		ImGuiIO& io = ImGui::GetIO();

		io.MouseWheel += event.GetScrolledY();
		io.MouseWheelH += event.GetScrolledX();
		return true;
	}

}
