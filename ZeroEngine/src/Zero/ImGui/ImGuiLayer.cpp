#include "zeropch.h"

#include "ImGuiLayer.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "imgui.h"
#include "backends/imgui_impl_opengl3.h"
#include "backends/imgui_impl_glfw.h"

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
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
		io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
		
		ImGuiStyle& style = ImGui::GetStyle();
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			style.WindowRounding = 0.0f;
			style.Colors[ImGuiCol_WindowBg].w = 1.0f;
		}

		Application& app = Application::GetInstance();
		Window* window = app.GetWindow();

		GLFWwindow* nativeWindow = static_cast<GLFWwindow*>(window->GetNativeWindow());
		
		ZERO_CORE_ASSERT(nativeWindow != nullptr, "Error in checking native window!!");
		
		ImGui_ImplGlfw_InitForOpenGL(nativeWindow, true);
		ImGui_ImplOpenGL3_Init("#version 460 core");
	}

	void ImGuiLayer::OnDetach()
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui::DestroyContext();
	}

	void ImGuiLayer::OnImGuiRender()
	{
		/*
		static char buffer[256] = "";
		ImGui::Begin("ImGui Test");
		ImGui::InputText("Enter the text", buffer, IM_ARRAYSIZE(buffer));
		//ImGui::Text("Its my life.");
		ImGui::Button("Press");
		ImGui::End();
		*/
		
		ImGui::ShowDemoWindow(&m_Show);
	}

	void ImGuiLayer::Begin()
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
	}

	void ImGuiLayer::End()
	{
		ImGuiIO& io = ImGui::GetIO();

		Application& app = Application::GetInstance();
		Window* window = app.GetWindow();
		io.DisplaySize = ImVec2(window->GetWidth(), window->GetHeight());

		io.DeltaTime = (m_Time > 0) ? glfwGetTime() - m_Time : 1.0f / 60.0f;
		m_Time = glfwGetTime();
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			GLFWwindow* backup_current_context = glfwGetCurrentContext();
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
			glfwMakeContextCurrent(backup_current_context);
		}
	}

}
