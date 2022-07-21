#include "zeropch.h"
#include "Zero/Renderer/OrthographicCamera.h"
#include "Renderer.h"
#include "Platform/OpenGL/OpenGLOrthographicCamera.h"


namespace Zero
{
	OrthographicCamera* OrthographicCamera::Create(float aspectRatio,float scale, glm::vec3 origin)
	{
		switch (Renderer::GetAPI())
		{
		case RenderAPI::API::None:
			ZERO_CORE_ASSERT(false, "No Renderer API Selected!!");
			return nullptr;

		case RenderAPI::API::OpenGL:
			return new OpenGLOrthographicCamera(aspectRatio,scale,origin);
		}

		ZERO_CORE_ASSERT(false, "Unknown Renderer API!!");
		return nullptr;
	}
}