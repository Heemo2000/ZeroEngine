#pragma once
#include <glad/glad.h>
#include<unordered_map>
#include "Zero/Renderer/Shader.h"


namespace Zero
{
	class OpenGLShader : public Shader
	{
	public:

		OpenGLShader(const std::string& filePath);
		OpenGLShader(const std::string& vertexSource, const std::string& fragmentSource);
		virtual void Bind() override;
		virtual void UnBind() override;
		virtual void UploadData(std::string name,const glm::mat4& value) override;
		virtual void UploadData(std::string name,const float& value) override;
		virtual void UploadData(std::string name, const int& value) override;
		virtual void UploadData(std::string name, const glm::vec4& value) override;
		virtual void UploadData(std::string name, const glm::vec3& value) override;
		~OpenGLShader();

	private:
		GLint GetUniformLocation(std::string name);
		std::unordered_map<GLenum,std::string> PreProcess(const std::string& source);
		void Compile(const std::unordered_map<GLenum, std::string> shaderSources);

		static GLenum ShaderTypeFromString(const std::string& type);
	private:
		uint32_t m_RendererID;
	};
}
