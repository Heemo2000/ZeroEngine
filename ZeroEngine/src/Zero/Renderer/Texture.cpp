#include "zeropch.h"

#include "Zero/Renderer/Texture.h"
#include "Zero/Renderer/RenderAPI.h"

#include "Platform/OpenGL/OpenGLTexture.h"

namespace Zero
{
	static Texture* Create(std::string& filePath, uint32_t textureSlot)
	{
		switch (RenderAPI::GetAPI())
		{
		case RenderAPI::API::None:
			ZERO_CORE_ASSERT(false, "No Renderer API Selected!!");
			return nullptr;

		case RenderAPI::API::OpenGL:
			return new OpenGLTexture(filePath, textureSlot);
		}

		ZERO_CORE_ASSERT(false, "Unknown Renderer API!!");
		return nullptr;
	}

	
}