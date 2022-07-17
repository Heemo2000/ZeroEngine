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
	std::shared_ptr<Zero::VertexArray> m_SmallSquareVA;
	std::shared_ptr<Zero::VertexArray> m_BigSquareVA;

	std::shared_ptr<Zero::VertexBuffer> m_smallSquareVBO;
	std::shared_ptr<Zero::IndexBuffer> m_IndexBuffer;

	std::shared_ptr<Zero::VertexBuffer> m_BigSquareVBO;
	std::shared_ptr<Zero::Shader> m_SmallSquareShader;
	std::shared_ptr<Zero::Shader> m_BigSquareShader;

	std::shared_ptr<Zero::OrthographicCamera> m_Camera;
	glm::vec4 m_ClearColor;
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