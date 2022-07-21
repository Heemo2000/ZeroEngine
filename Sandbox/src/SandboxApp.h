#pragma once
#include <Zero.h>
#include <glm/glm.hpp>

class SandboxLayer : public Zero::Layer
{
public:
	SandboxLayer();
	void OnUpdate() override;
	void OnEvent(Zero::Event& event) override;
	void OnImGuiRender() override;
private:
	bool OnWindowResized(Zero::WindowResizedEvent& event);
	bool OnKeyPressed(Zero::KeyPressedEvent& event);
	bool OnKeyTyped(Zero::KeyTypedEvent& event);
	bool OnMouseScrolled(Zero::MouseScrolledEvent& event);
	

private:
	std::shared_ptr<Zero::VertexArray> m_SmallSquareVA;
	std::shared_ptr<Zero::VertexArray> m_BigSquareVA;

	std::shared_ptr<Zero::VertexBuffer> m_smallSquareVBO;
	std::shared_ptr<Zero::IndexBuffer> m_IndexBuffer;

	std::shared_ptr<Zero::VertexBuffer> m_BigSquareVBO;
	std::shared_ptr<Zero::Shader> m_SmallSquareShader;
	std::shared_ptr<Zero::Shader> m_BigSquareShader;

	std::shared_ptr<Zero::OrthographicCamera> m_Camera;
	glm::vec4 m_ClearColor;
	
	glm::vec3 m_CameraPosition = glm::vec3(0.0f, 0.0f, 1.0f);
	float m_CameraMoveSpeed = 0.01f;
	float m_CameraRotation = 0.0f;
	float m_CameraRotationSpeed = 2.0f;
};

class Sandbox : public Zero::Application
{
public:
	Sandbox()
	{
		PushLayer(new SandboxLayer());
	}

	~Sandbox()
	{

	}
};