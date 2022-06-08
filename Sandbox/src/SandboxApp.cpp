#include <Zero.h>

class ExampleLayer1 : public Zero::Layer
{
public:
	ExampleLayer1() : Zero::Layer("ExampleLayer1") {}

	void OnUpdate() override
	{
		ZERO_CLIENT_INFO("ExampleLayer1 : Update");
	}

	void OnEvent(Zero::Event& event) override
	{
		ZERO_CLIENT_TRACE("{0}", event.ToString());
	}
};
class Sandbox : public Zero::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer1());
		PushOverlay(new Zero::ImGuiLayer());
	}

	~Sandbox()
	{

	}
};


Zero::Application* Zero::CreateApplication()
{
	return new Sandbox();
}
