#pragma once
#include <glad/glad.h>
#include "Zero/Renderer/Shader.h"


namespace Zero
{
	class OpenGLShader : public Shader
	{
	public:

		OpenGLShader(const std::string& vertexSource, const std::string& fragmentSource);
		virtual void Bind() override;
		virtual void UnBind() override;
		virtual void UploadData(std::string name,const glm::mat4& value) override;
		~OpenGLShader();
	private:
		GLint GetUniformLocation(std::string name);
		
	private:
		uint32_t m_RendererID;
	};
}
