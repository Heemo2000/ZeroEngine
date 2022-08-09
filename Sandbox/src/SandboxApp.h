#pragma once
#include <Zero.h>
#include <glm/glm.hpp>

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
	float m_CameraMoveSpeed = 1.0f;
	float m_CameraRotation = 0.0f;
	float m_CameraRotationSpeed = 20.0f;

	glm::vec3 m_SmallSquarePosition = glm::vec3(0.0f, 0.0f, 0.0f);
	float m_SmallSquareRotation = 0.0f;
	float m_SmallSquareMoveSpeed = 1.0f;
	float m_SmallSquareRotationSpeed = 20.0f;

	glm::vec4 m_LightColor = glm::vec4(1.0f,1.0f,1.0f,1.0f);
	float m_ElapsedTime = 0.0f;

	Zero::Transform m_SmallSquareTransform = Zero::Transform(m_SmallSquarePosition);
	
	Zero::Transform m_BigSquareTransform = Zero::Transform(glm::vec3(1.0f,0.0f,0.0f));
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