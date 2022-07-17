#pragma once
#include <glad/glad.h>
#include "Zero/Renderer/Shader.h"
#include "Zero/Renderer/OrthographicCamera.h"



namespace Zero
{
	class OpenGLOrthographicCamera : public OrthographicCamera
	{
	public:
		
		OpenGLOrthographicCamera(unsigned int width, unsigned int height, glm::vec3 origin);
		virtual void CalculateViewProjectionMatrix() override;
		virtual glm::mat4 GetViewProjectionMatrix() const override;
		virtual void SetPosition(glm::vec3& position) override;
		virtual void SetScale(float& scale) override;
		virtual void SetWidth(unsigned int width) override;
		virtual void SetHeight(unsigned int height) override;
		virtual ~OpenGLOrthographicCamera() override;


	private:
		glm::vec3 m_Position;
		glm::vec3 m_Up = glm::vec3(0.0f, 1.0f, 0.0f);
		glm::vec3 m_Forward = glm::vec3(0.0f, 0.0f, 1.0f);
		glm::mat4 m_View = glm::mat4(1.0f);
		glm::mat4 m_Projection = glm::mat4(1.0f);
		CameraData m_CameraData;

		float m_AspectRatio;
		float m_Scale;
		float m_Left;
		float m_Right;
		float m_Top;
		float m_Bottom;
	};
}
