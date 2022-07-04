#include "zeropch.h"
#include "Zero/Renderer/Shader.h"
#include "Zero/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace Zero
{
	Shader* Shader::Create(const std::string& vertexSource, const std::string& fragmentSource)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::None:
			ZERO_CORE_ASSERT(false, "No Renderer API Selected!!");
			return nullptr;

		case RendererAPI::OpenGL:
			return new OpenGLShader(vertexSource, fragmentSource);
		}

		ZERO_CORE_ASSERT(false, "Unknown Renderer API!!");
		return nullptr;
	}
}