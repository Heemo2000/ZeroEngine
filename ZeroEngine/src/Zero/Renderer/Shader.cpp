#include "zeropch.h"
#include "Zero/Renderer/Shader.h"
#include "Zero/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace Zero
{
	Zero::Ref<Shader> Shader::Create(const std::string& filePath)
	{
		switch (Renderer::GetAPI())
		{
		case RenderAPI::API::None:
			ZERO_CORE_ASSERT(false, "No Renderer API Selected!!");
			return nullptr;

		case RenderAPI::API::OpenGL:
			return std::make_shared<OpenGLShader>(filePath);
		}

		ZERO_CORE_ASSERT(false, "Unknown Renderer API!!");
		return nullptr;
	}
	Zero::Ref<Shader> Shader::Create(const std::string& name,const std::string& vertexSource, const std::string& fragmentSource)
	{
		switch (Renderer::GetAPI())
		{
		case RenderAPI::API::None:
			ZERO_CORE_ASSERT(false, "No Renderer API Selected!!");
			return nullptr;

		case RenderAPI::API::OpenGL:
			return std::make_shared<OpenGLShader>(name,vertexSource,fragmentSource);
		}

		ZERO_CORE_ASSERT(false, "Unknown Renderer API!!");
		return nullptr;
	}

	void ShaderLibrary::Add(const std::string& name,const Zero::Ref<Zero::Shader>& shader)
	{
		ZERO_CORE_ASSERT(m_Shaders.find(name) == m_Shaders.end(), "Shader already exists!");
		m_Shaders[name] = shader;
	}
	void ShaderLibrary::Add(const Zero::Ref<Zero::Shader>& shader)
	{
		auto name = shader->GetName();
		m_Shaders[name] = shader;
	}
	Zero::Ref<Shader> ShaderLibrary::Load(const std::string& filePath)
	{
		auto shader = Zero::Shader::Create(filePath);
		Add(shader);
		return shader;
	}
	Zero::Ref<Shader> ShaderLibrary::Load(const std::string& name, const std::string& filePath)
	{
		auto shader = Zero::Shader::Create(filePath);
		Add(name, shader);
		return shader;
	}
	Zero::Ref<Shader> ShaderLibrary::Get(const std::string& name)
	{
		ZERO_CORE_ASSERT(m_Shaders.find(name) != m_Shaders.end(), "Shader not found!");
		return m_Shaders[name];
	}
}