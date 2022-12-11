#pragma once
#include <Zero.h>
#include <glm/glm.hpp>
#include <Zero/EntryPoint.h>
#include "Sandbox2D.h"

class Quad
{
private:
	Zero::Transform m_Transform;
	Zero::Ref<Zero::VertexArray> m_QuadVA;
	Zero::Ref<Zero::VertexBuffer> m_QuadVB;
	Zero::Ref<Zero::IndexBuffer> m_QuadIB;
	Zero::Ref<Zero::Shader> m_Shader;
	bool m_Enabled;
	glm::vec4 m_Color;

public:
	Quad(glm::vec3 worldPosition);

	bool IsEnabled();

	void DrawQuad();
	void SetEnabled(bool enabled);
	void SetPosition(glm::vec3 position);
	void SetScale(glm::vec3 scale);
	void SetColor(glm::vec4 color);
};
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

	glm::vec3 m_Origin = glm::vec3(0.0f,0.0f,0.0f);
	uint32_t m_N = 20;


	Zero::InstanceManager* m_QuadInstances;
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