#include "zeropch.h"
#include "Platform/OpenGL/OpenGLOrthographicCamera.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
namespace Zero
{
	OpenGLOrthographicCamera::OpenGLOrthographicCamera(float aspectRatio,float scale, glm::vec3 origin) :
		m_Position(origin),
		m_Scale(scale),
		m_AspectRatio(aspectRatio),
		m_Left(-aspectRatio * scale),
		m_Right(aspectRatio * scale),
		m_Top(scale),
		m_Bottom(-scale)
	{
		RecalculateViewProjectionMatrix();
	}
	
	void OpenGLOrthographicCamera::RecalculateViewProjectionMatrix()
	{
		glm::mat4 transform = glm::inverse(glm::translate(glm::mat4(1.0f), m_Position)) * glm::rotate(glm::mat4(1.0f), 
											 glm::radians(m_Rotation), 
											 glm::vec3(0.0f, 0.0f, 1.0f));

		m_View = transform;//glm::inverse(transform);

		m_Left = -m_AspectRatio * m_Scale;
		m_Right = m_AspectRatio * m_Scale;
		m_Top = m_Scale;
		m_Bottom = -m_Scale;

		m_Projection = glm::ortho(m_Left, m_Right, m_Bottom, m_Top, -1.0f, 1.0f);
	}

	glm::mat4 OpenGLOrthographicCamera::GetViewProjectionMatrix() const
	{
		return m_View * m_Projection;
	}

	glm::vec3 OpenGLOrthographicCamera::GetPosition() const
	{
		return m_Position;
	}

	void OpenGLOrthographicCamera::SetPosition(const glm::vec3& position)
	{
		m_Position = position;
		RecalculateViewProjectionMatrix();
	}

	float OpenGLOrthographicCamera::GetScale() const
	{
		return m_Scale;
	}

	void OpenGLOrthographicCamera::SetScale(const float& scale)
	{
		if (scale <= 0.5f)
		{
			return;
		}
		m_Scale = scale;
		RecalculateViewProjectionMatrix();
	}

	float OpenGLOrthographicCamera::GetRotation() const
	{
		return m_Rotation;
	}

	void OpenGLOrthographicCamera::SetRotation(const float& rotation)
	{
		m_Rotation = rotation;
		RecalculateViewProjectionMatrix();
	}

	float OpenGLOrthographicCamera::GetAspectRatio() const
	{
		return m_AspectRatio;
	}

	void OpenGLOrthographicCamera::SetAspectRatio(const float& aspectRatio)
	{
		m_AspectRatio = aspectRatio;
		RecalculateViewProjectionMatrix();
	}


	OpenGLOrthographicCamera::~OpenGLOrthographicCamera()
	{
	}
}

