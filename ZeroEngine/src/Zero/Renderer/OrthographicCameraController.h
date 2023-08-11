#pragma once
#include <glm/glm.hpp>
#include "OrthographicCamera.h"
#include "Zero/Core/Timestep.h"

#include "Zero/Events/Event.h"
#include "Zero/Events/EventDispatcher.h"
#include "Zero/Events/ApplicationEvent.h"
#include "Zero/Events/MouseScrolledEvent.h"

namespace Zero
{
	class OrthographicCameraController
	{
	public:
		OrthographicCameraController(float aspectRatio, bool allowRotation, float zNear = -1000.0f, float zfar = 1000.0f);
		void OnUpdate(Timestep ts);
		void OnEvent(Event& e);

		OrthographicCamera GetCamera();
	private:
		bool OnMouseScrolled(Zero::MouseScrolledEvent& e);
		bool OnWindowResized(Zero::WindowResizedEvent& e);

	private:
		float m_AspectRatio;
		float m_ZoomLevel = 1.0f;
		float m_ZNear;
		float m_ZFar;
		OrthographicCamera m_Camera;

		bool m_AllowRotation;

		glm::vec3 m_Position = {0.0f,0.0f,0.0f};
		float m_Rotation = 0.0f;
		float m_MoveSpeed = 1.0f;
		float m_RotateSpeed = 1.0f;
		
	};
}
