#pragma once
#include <Zero.h>
#include <glm/glm.hpp>


class Sandbox2D : public Zero::Layer
{
public:
	Sandbox2D();
	void OnDetach() override;
	void OnAttach() override;
	void OnUpdate(Zero::Timestep timestep) override;
	void OnEvent(Zero::Event& event) override;
	void OnImGuiRender() override;

private:
	glm::vec3 ScreenToWorldPoint(glm::vec3 position);
	bool CreateQuad();
private:
	bool OnWindowResized(Zero::WindowResizedEvent& event);
	bool OnKeyPressed(Zero::KeyPressedEvent& event);
	bool OnKeyTyped(Zero::KeyTypedEvent& event);
	bool OnMouseScrolled(Zero::MouseScrolledEvent& event);
	bool OnMouseClicked(Zero::MouseButtonClickedEvent& event);

private:
	Zero::OrthographicCameraController m_CameraController;
	glm::vec4 m_ClearColor;

	glm::vec3 m_CameraPosition = glm::vec3(0.0f, 0.0f, 1.0f);
	float m_CameraMoveSpeed = 1.0f;
	float m_CameraRotation = 0.0f;
	float m_CameraRotationSpeed = 20.0f;

	float m_ElapsedTime = 0.0f;

	bool m_Open = true;
	uint32_t m_ClickCount = 0;
	std::vector<glm::vec3> m_Points;
	bool m_MouseHold;
	glm::vec3 previousPoint = glm::vec3(0.0f,0.0f,0.0f);
};