#include <Zero.h>
#include "imgui.h"

class ExampleLayer1 : public Zero::Layer
{
public:
	ExampleLayer1() : Zero::Layer("ExampleLayer1") {}

	void OnUpdate() override
	{
		//ZERO_CLIENT_INFO("ExampleLayer1 : Update");
	}

	void OnEvent(Zero::Event& event) override
	{
		ZERO_CLIENT_TRACE("{0}", event.ToString());
	}

	void OnImGuiRender() override
	{
		ImGui::Begin("Test");
		ImGui::Text("ImGui working in Sandbox");
		ImGui::End();
	}
};
class Sandbox : public Zero::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer1());
	}

	~Sandbox()
	{

	}
};


Zero::Application* Zero::CreateApplication()
{
	return new Sandbox();
}
