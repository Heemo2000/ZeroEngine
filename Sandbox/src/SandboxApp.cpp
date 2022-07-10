#include <Zero.h>
#include "imgui.h"

class ExampleLayer1 : public Zero::Layer
{
public:
	ExampleLayer1() : Zero::Layer("ExampleLayer1") {}

	void OnUpdate() override
	{
		
	}

	void OnEvent(Zero::Event& event) override
	{
		
	}

	void OnImGuiRender() override
	{

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
