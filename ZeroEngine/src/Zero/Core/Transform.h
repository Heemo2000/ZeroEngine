#pragma once
#include "Zero/Core.h"
#include <glm/glm.hpp>

namespace Zero
{
	class ZERO_API Transform
	{
	public:
		Transform(glm::vec3 position,float rotation = 0.0f,glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f));
		glm::vec3 GetPosition();
		float GetRotation();
		glm::vec3 GetScale();
		glm::mat4 GetTransformationMatrix();

		void SetPosition(glm::vec3 position);
		void SetRotation(float rotation);
		void SetScale(glm::vec3 scale);

	private:
		glm::vec3 m_Position;
		float m_Rotation;
		glm::vec3 m_Scale;
	};
}
