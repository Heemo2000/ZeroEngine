#pragma once
#include "Zero/Renderer/Shader.h"


namespace Zero
{
	class OpenGLShader : public Shader
	{
	public:

		OpenGLShader(const std::string& vertexSource, const std::string& fragmentSource);
		virtual void Bind() override;
		virtual void UnBind() override;

		~OpenGLShader();
	private:
		uint32_t m_RendererID;
	};
}
