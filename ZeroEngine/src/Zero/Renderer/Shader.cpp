#include "zeropch.h"
#include "Zero/Renderer/Shader.h"
#include "Zero/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace Zero
{
	Shader* Shader::Create(const std::string& filePath)
	{
		switch (Renderer::GetAPI())
		{
		case RenderAPI::API::None:
			ZERO_CORE_ASSERT(false, "No Renderer API Selected!!");
			return nullptr;

		case RenderAPI::API::OpenGL:
			return new OpenGLShader(filePath);
		}

		ZERO_CORE_ASSERT(false, "Unknown Renderer API!!");
		return nullptr;
	}
	Shader* Shader::Create(const std::string& vertexSource, const std::string& fragmentSource)
	{
		switch (Renderer::GetAPI())
		{
		case RenderAPI::API::None:
			ZERO_CORE_ASSERT(false, "No Renderer API Selected!!");
			return nullptr;

		case RenderAPI::API::OpenGL:
			return new OpenGLShader(vertexSource, fragmentSource);
		}

		ZERO_CORE_ASSERT(false, "Unknown Renderer API!!");
		return nullptr;
	}
}