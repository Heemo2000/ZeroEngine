#include "zeropch.h"
#include "Transform.h"
#include <glm/gtc/matrix_transform.hpp>

namespace Zero
{
	Transform::Transform(glm::vec3 position,
						 float rotation,
						 glm::vec3 scale) :
						 m_Position(position), m_Rotation(rotation), m_Scale(scale)
						{}


	glm::vec3 Transform::GetPosition()
	{
		return m_Position;
	}
	float Transform::GetRotation()
	{
		return m_Rotation;
	}
	glm::vec3 Transform::GetScale()
	{
		return m_Scale;
	}

	glm::mat4 Transform::GetTransformationMatrix()
	{
		glm::mat4 transform =  glm::translate(glm::mat4(1.0f), m_Position) * 
							glm::rotate(glm::mat4(1.0f),glm::radians(m_Rotation),glm::vec3(0.0f,0.0f,1.0f)) *
							glm::scale(glm::mat4(1.0f),m_Scale);
		return transform;
	}

	void Transform::SetPosition(glm::vec3 position)
	{
		m_Position = position;
	}
	void Transform::SetRotation(float rotation)
	{
		m_Rotation = rotation;
	}
	void Transform::SetScale(glm::vec3 scale)
	{
		m_Scale = scale;
	}


}