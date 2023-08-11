#include "zeropch.h"
#include "OrthographicCameraController.h"
#include "Zero/KeyCodes.h"
#include "Zero/Core/Timestep.h"
#include "Zero/Input.h"

Zero::OrthographicCameraController::OrthographicCameraController(float aspectRatio,bool allowRotation, float zNear,
																 float zFar) :
	m_AspectRatio(aspectRatio),
	m_AllowRotation(allowRotation),
	m_ZNear(zNear),
	m_ZFar(zFar),
	m_Camera(-aspectRatio * m_ZoomLevel,aspectRatio * m_ZoomLevel,-m_ZoomLevel,m_ZoomLevel,zNear,zFar)
{
}

void Zero::OrthographicCameraController::OnUpdate(Timestep ts)
{
	if (Zero::Input::IsKeyPressed(ZERO_KEY_W))
	{
		m_Position.y += m_MoveSpeed * ts.GetDeltaTimeInSec();
	}

	else if (Zero::Input::IsKeyPressed(ZERO_KEY_S))
	{
		m_Position.y -= m_MoveSpeed * ts.GetDeltaTimeInSec();
	}

	if (Zero::Input::IsKeyPressed(ZERO_KEY_A))
	{
		m_Position.x -= m_MoveSpeed * ts.GetDeltaTimeInSec();
	}

	else if (Zero::Input::IsKeyPressed(ZERO_KEY_D))
	{
		m_Position.x += m_MoveSpeed * ts.GetDeltaTimeInSec();
	}

	if (Zero::Input::IsKeyPressed(ZERO_KEY_Q))
	{
		m_Rotation += m_RotateSpeed * ts.GetDeltaTimeInSec();
	}

	else if (Zero::Input::IsKeyPressed(ZERO_KEY_E))
	{
		m_Rotation -= m_RotateSpeed * ts.GetDeltaTimeInSec();
	}

	m_Camera.SetPosition(m_Position);
	m_Camera.SetRotation(m_Rotation);
}

void Zero::OrthographicCameraController::OnEvent(Event& e)
{
	Zero::EventDispatcher eventDispatcher(e);
	eventDispatcher.Dispatch<Zero::MouseScrolledEvent>(ZERO_BIND_EVENT_FN(OrthographicCameraController::OnMouseScrolled));
	eventDispatcher.Dispatch<Zero::WindowResizedEvent>(ZERO_BIND_EVENT_FN(OrthographicCameraController::OnWindowResized));
}

Zero::OrthographicCamera Zero::OrthographicCameraController::GetCamera()
{
	return m_Camera;
}

bool Zero::OrthographicCameraController::OnMouseScrolled(Zero::MouseScrolledEvent& e)
{
	float amount = e.GetScrolledY();
	if (m_ZoomLevel - amount >= 0.25f)
	{
		m_ZoomLevel -= amount;
		ZERO_CORE_INFO("Changing Zoom level");
	}
	
	m_Camera.SetProjectionMatrix(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel,m_ZNear, m_ZFar);
	return false;
}

bool Zero::OrthographicCameraController::OnWindowResized(Zero::WindowResizedEvent& event)
{
	float aspectRatio = (float)event.GetWidth() / (float)event.GetHeight();
	
	m_AspectRatio = aspectRatio;
	m_Camera.SetProjectionMatrix(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel, m_ZNear, m_ZFar);
	return false;
}
