#include "zeropch.h"
#include "Platform/OpenGL/OpenGLOrthographicCamera.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace Zero
{
	OpenGLOrthographicCamera::OpenGLOrthographicCamera(unsigned int width, unsigned int height, glm::vec3 origin) :
		m_Position(origin), 
		m_CameraData(width, height, CameraMode::Orthographic),
		m_Scale(1.0f),
		m_AspectRatio((float)width / height),
		m_Left(-m_AspectRatio * m_Scale),
		m_Right(m_AspectRatio* m_Scale),
		m_Top(m_Scale),
		m_Bottom(-m_Scale)
	{}
	
	void OpenGLOrthographicCamera::CalculateViewProjectionMatrix()
	{

		m_View = glm::lookAt(m_Position, m_Position + m_Forward, m_Up);

		m_AspectRatio = (float)(m_CameraData.Width / m_CameraData.Height);
		m_Left = -m_AspectRatio * m_Scale;
		m_Right = m_AspectRatio * m_Scale;
		m_Top = m_Scale;
		m_Bottom = -m_Scale;

		m_Projection = glm::ortho(m_Left, m_Right, m_Bottom, m_Top, 0.1f, 100.0f);
	}

	glm::mat4 OpenGLOrthographicCamera::GetViewProjectionMatrix() const
	{
		return m_View * m_Projection;
	}

	void OpenGLOrthographicCamera::SetPosition(glm::vec3& position)
	{
		m_Position = position;
	}

	void OpenGLOrthographicCamera::SetScale(float& scale)
	{
		m_Scale = scale;
	}

	void OpenGLOrthographicCamera::SetWidth(unsigned int width)
	{
		m_CameraData.Width = width;
	}

	void OpenGLOrthographicCamera::SetHeight(unsigned int height)
	{
		m_CameraData.Height = height;
	}


	OpenGLOrthographicCamera::~OpenGLOrthographicCamera()
	{
	}
}

