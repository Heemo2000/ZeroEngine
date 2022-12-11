#pragma once
#include <glm/glm.hpp>

namespace Zero
{
	class OrthographicCamera
	{
	public:
		OrthographicCamera(float left,float right,float down,float up);

		void SetProjectionMatrix(float left, float right,float down,float up);
		
		glm::mat4 GetViewProjectionMatrix() const;

		glm::vec3 GetPosition() const;
		void SetPosition(const glm::vec3& position);
		
		float GetRotation() const;
		void SetRotation(const float& rotation);
		
		~OrthographicCamera();

	private:
		void RecalculateViewProjectionMatrix();

	private:
		glm::mat4 m_View = glm::mat4(1.0f);
		glm::mat4 m_Projection = glm::mat4(1.0f);

		glm::vec3 m_Position = { 0.0f,0.0f,0.0f };
		float m_Rotation = 0.0f;
	};
}
