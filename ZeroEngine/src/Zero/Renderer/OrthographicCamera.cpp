#include "zeropch.h"
#include "Zero/Renderer/OrthographicCamera.h"
#include "Renderer.h"
#include "Platform/OpenGL/OpenGLOrthographicCamera.h"


namespace Zero
{
	OrthographicCamera* OrthographicCamera::Create(unsigned int width, unsigned int height, glm::vec3 origin)
	{
		switch (Renderer::GetAPI())
		{
		case RenderAPI::API::None:
			ZERO_CORE_ASSERT(false, "No Renderer API Selected!!");
			return nullptr;

		case RenderAPI::API::OpenGL:
			return new OpenGLOrthographicCamera(width,height,origin);
		}

		ZERO_CORE_ASSERT(false, "Unknown Renderer API!!");
		return nullptr;
	}
}