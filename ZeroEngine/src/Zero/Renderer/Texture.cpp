#include "zeropch.h"

#include "Zero/Renderer/Texture.h"
#include "Zero/Renderer/RenderAPI.h"

#include "Platform/OpenGL/OpenGLTexture2D.h"

namespace Zero
{
	Texture2D* Texture2D::Create(const std::string& filePath,const uint32_t& textureSlot)
	{
		switch (RenderAPI::GetAPI())
		{
		case RenderAPI::API::None:
			ZERO_CORE_ASSERT(false, "No Renderer API Selected!!");
			return nullptr;

		case RenderAPI::API::OpenGL:
			return new OpenGLTexture2D(filePath, textureSlot);
		}

		ZERO_CORE_ASSERT(false, "Unknown Renderer API!!");
		return nullptr;
	}

	Texture2D* Texture2D::Create(const uint32_t& singlePixelData, const uint32_t& textureSlot)
	{
		switch (RenderAPI::GetAPI())
		{
		case RenderAPI::API::None:
			ZERO_CORE_ASSERT(false, "No Renderer API Selected!!");
			return nullptr;

		case RenderAPI::API::OpenGL:
			return new OpenGLTexture2D(singlePixelData, textureSlot);
		}

		ZERO_CORE_ASSERT(false, "Unknown Renderer API!!");
		return nullptr;
	}

}