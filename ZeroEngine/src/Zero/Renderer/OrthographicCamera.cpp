#include "zeropch.h"
#include "Zero/Renderer/OrthographicCamera.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
namespace Zero
{
	OrthographicCamera::OrthographicCamera(float left, float right, float down, float up,float zNear, float zFar) :
		m_Projection(glm::ortho(left, right, down, up, zNear, zFar)), m_View(1.0f)
	{
	}

	void OrthographicCamera::SetProjectionMatrix(float left, float right, float down, float up, float zNear, float zFar)
	{
		m_Projection = glm::ortho(left, right, down, up, zNear, zFar);
	}

	void OrthographicCamera::RecalculateViewProjectionMatrix()
	{
		glm::mat4 transform = glm::inverse(glm::translate(glm::mat4(1.0f), m_Position)) * glm::rotate(glm::mat4(1.0f),
			glm::radians(m_Rotation),
			glm::vec3(0.0f, 0.0f, 1.0f));

		m_View = transform;//glm::inverse(transform);
	}

	glm::mat4 OrthographicCamera::GetViewProjectionMatrix() const
	{
		return m_View * m_Projection;
	}

	glm::vec3 OrthographicCamera::GetPosition() const
	{
		return m_Position;
	}

	void OrthographicCamera::SetPosition(const glm::vec3& position)
	{
		m_Position = position;
		RecalculateViewProjectionMatrix();
	}

	float OrthographicCamera::GetRotation() const
	{
		return m_Rotation;
	}

	void OrthographicCamera::SetRotation(const float& rotation)
	{
		m_Rotation = rotation;
		RecalculateViewProjectionMatrix();
	}

	glm::mat4 OrthographicCamera::GetViewMatrix() const
	{
		return m_View;
	}

	glm::mat4 OrthographicCamera::GetProjectionMatrix() const
	{
		return m_Projection;
	}


	OrthographicCamera::~OrthographicCamera()
	{
	}
}

