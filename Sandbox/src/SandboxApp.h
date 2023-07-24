#pragma once
#include <Zero.h>
#include <glm/glm.hpp>
#include <Zero/EntryPoint.h>
#include "Sandbox2D.h"

class SandboxLayer : public Zero::Layer
{
public:
	SandboxLayer();
	void OnUpdate(Zero::Timestep timestep) override;
	void OnEvent(Zero::Event& event) override;
	void OnImGuiRender() override;
private:
	bool OnWindowResized(Zero::WindowResizedEvent& event);
	bool OnKeyPressed(Zero::KeyPressedEvent& event);
	bool OnKeyTyped(Zero::KeyTypedEvent& event);
	bool OnMouseScrolled(Zero::MouseScrolledEvent& event);
	bool OnMouseClicked(Zero::MouseButtonClickedEvent& event);

private:
	//Zero::Ref<Zero::OrthographicCamera> m_Camera;
	glm::vec4 m_ClearColor;
	
	glm::vec3 m_CameraPosition = glm::vec3(0.0f, 0.0f, 1.0f);
	float m_CameraMoveSpeed = 1.0f;
	float m_CameraRotation = 0.0f;
	float m_CameraRotationSpeed = 20.0f;

	float m_ElapsedTime = 0.0f;
	};

class Sandbox : public Zero::Application
{
public:
	Sandbox()
	{
		PushLayer(new Sandbox2D());
	}

	~Sandbox()
	{

	}
};