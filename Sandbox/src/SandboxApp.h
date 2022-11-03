#pragma once
#include <Zero.h>
#include <glm/glm.hpp>


class Quad
{
private:
	Zero::Transform m_Transform;
	Zero::Ref<Zero::VertexArray> m_VertexArray;
	Zero::Ref<Zero::VertexBuffer> m_VertexBuffer;
	Zero::Ref<Zero::IndexBuffer> m_IndexBuffer;
	Zero::Ref<Zero::Shader> m_Shader;

public:
	Quad(glm::vec3 worldPosition);
	void DrawQuad();
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
	Zero::Ref<Zero::VertexArray> m_SmallSquareVA;

	
	Zero::Ref<Zero::OrthographicCamera> m_Camera;
	std::vector<Zero::Ref<Quad>> m_Quads;
	glm::vec4 m_ClearColor;
	
	glm::vec3 m_CameraPosition = glm::vec3(0.0f, 0.0f, 1.0f);
	float m_CameraMoveSpeed = 1.0f;
	float m_CameraRotation = 0.0f;
	float m_CameraRotationSpeed = 20.0f;

	float m_ElapsedTime = 0.0f;

	Zero::Ref<Quad> m_Quad;
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