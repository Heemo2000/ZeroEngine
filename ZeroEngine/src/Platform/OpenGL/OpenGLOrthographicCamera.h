#pragma once
#include <glad/glad.h>
#include "Zero/Renderer/Shader.h"
#include "Zero/Renderer/OrthographicCamera.h"



namespace Zero
{
	class OpenGLOrthographicCamera : public OrthographicCamera
	{
	public:
		
		OpenGLOrthographicCamera(float aspectRatio,float scale, glm::vec3 origin);
		virtual void SetProjectionMatrix(glm::mat4 projection);

		virtual glm::mat4 GetViewProjectionMatrix() const override;
		virtual glm::vec3 GetPosition() const override;
		virtual void SetPosition(const glm::vec3& position) override;
		virtual float GetScale() const override;
		virtual void SetScale(const float& scale) override;
		virtual float GetRotation() const override;
		virtual void SetRotation(const float& rotation) override;
		virtual float GetAspectRatio() const override;
		virtual void SetAspectRatio(const float& aspectRatio) override;
		virtual ~OpenGLOrthographicCamera() override;

	protected:
		virtual void RecalculateViewProjectionMatrix() override;

	private:
		glm::vec3 m_Position;
		glm::mat4 m_View = glm::mat4(1.0f);
		glm::mat4 m_Projection = glm::mat4(1.0f);

		float m_AspectRatio;
		float m_Scale;
		float m_Rotation;
		float m_Left;
		float m_Right;
		float m_Top;
		float m_Bottom;
	};
}
