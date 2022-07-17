#pragma once
#include <glm/glm.hpp>



namespace Zero
{
	enum class CameraMode
	{
		None = 0,
		Orthographic,
		Perspective
	};
	struct CameraData
	{
		unsigned int Width;
		unsigned int Height;
		CameraMode Mode;

		CameraData(unsigned int width, 
				   unsigned int height, 
				   CameraMode mode) :
					Width(width), 
					Height(height), 
					Mode(mode)
					{}
	};


	class ZERO_API OrthographicCamera
	{
	public:
		static OrthographicCamera* Create(unsigned int width, unsigned int height, glm::vec3 origin);

		virtual void CalculateViewProjectionMatrix() = 0;
		virtual glm::mat4 GetViewProjectionMatrix() const = 0;
		virtual void SetPosition(glm::vec3& position) = 0;
		virtual void SetScale(float& scale) = 0;
		virtual void SetWidth(unsigned int width) = 0;
		virtual void SetHeight(unsigned int height) = 0;
		virtual ~OrthographicCamera() {}	
	};
}
