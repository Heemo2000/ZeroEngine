#pragma once
#include <glm/glm.hpp>



namespace Zero
{
	class ZERO_API OrthographicCamera
	{
	public:
		static OrthographicCamera* Create(float aspectRatio,float scale, glm::vec3 position);

		virtual glm::mat4 GetViewProjectionMatrix() const = 0;
		virtual glm::vec3 GetPosition() const = 0;
		virtual void SetPosition(const glm::vec3& position) = 0;
		virtual float GetScale() const = 0;
		virtual void SetScale(const float& scale) = 0;
		virtual float GetRotation() const = 0;
		virtual void SetRotation(const float& rotation) = 0;
		virtual float GetAspectRatio() const = 0;
		virtual void SetAspectRatio(const float& aspectRatio) = 0;
		virtual ~OrthographicCamera() {}	

	protected:
		virtual void RecalculateViewProjectionMatrix() = 0;
	};
}
