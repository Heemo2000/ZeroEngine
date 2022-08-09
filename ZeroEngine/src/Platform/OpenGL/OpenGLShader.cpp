#include "zeropch.h"
#include "OpenGLShader.h"
#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>
namespace Zero
{
	OpenGLShader::OpenGLShader(const std::string& vertexSource, const std::string& fragmentSource)
	{
		const char* vertexShaderContents = vertexSource.c_str();
		const char* fragmentShaderContents = fragmentSource.c_str();



		GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertexShader, 1, &vertexShaderContents, NULL);
		glCompileShader(vertexShader);

		GLint compileSuccess;
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &compileSuccess);

		if (!compileSuccess)
		{
			GLint logLength = 0;
			glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &logLength);
			std::vector<GLchar> infoLog(logLength);
			glGetShaderInfoLog(vertexShader, logLength, &logLength, &infoLog[0]);

			glDeleteShader(vertexShader);
			ZERO_CORE_ERROR("{0}", infoLog);
			ZERO_CORE_ASSERT(false, "Vertex shader compilation failure!!");
			return;
		}

		GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragmentShader, 1, &fragmentShaderContents, NULL);
		glCompileShader(fragmentShader);

		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &compileSuccess);

		if (!compileSuccess)
		{
			GLint logLength = 0;
			glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &logLength);
			std::vector<GLchar> infoLog(logLength);

			glGetShaderInfoLog(fragmentShader, logLength, &logLength, &infoLog[0]);
			glDeleteShader(fragmentShader);
			glDeleteShader(vertexShader);

			ZERO_CORE_ERROR("{0}", infoLog);
			ZERO_CORE_ASSERT(false, "Fragment shader compilation failure!!");
			return;
		}

		m_RendererID = glCreateProgram();
		glAttachShader(m_RendererID, vertexShader);
		glAttachShader(m_RendererID, fragmentShader);

		glLinkProgram(m_RendererID);

		GLint isLinked = 0;
		glGetProgramiv(m_RendererID, GL_LINK_STATUS, (int*)&isLinked);
		if (isLinked == GL_FALSE)
		{
			GLint infoLength = 0;
			glGetProgramiv(m_RendererID, GL_INFO_LOG_LENGTH, &infoLength);

			std::vector<GLchar> infoLog(infoLength);
			glGetProgramInfoLog(m_RendererID, infoLength, &infoLength, &infoLog[0]);

			// We don't need the program anymore.
			glDeleteProgram(m_RendererID);
			// Don't leak shaders either.
			glDeleteShader(vertexShader);
			glDeleteShader(fragmentShader);

			ZERO_CORE_ERROR("{0}", infoLog);
			ZERO_CORE_ASSERT(false, "Shader program Linking failed!!");
			return;
		}

		glDetachShader(m_RendererID, vertexShader);
		glDetachShader(m_RendererID, fragmentShader);
	}

	void OpenGLShader::Bind()
	{
		glUseProgram(m_RendererID);
	}

	void OpenGLShader::UnBind()
	{
		glUseProgram(0);
	}

	void OpenGLShader::UploadData(std::string name,const glm::mat4& value)
	{
		GLint uniformLocation = GetUniformLocation(name);
		
		if (uniformLocation == -1)
		{
			std::string errorLog = "Not able to upload matrix data to location named " + name;
			ZERO_CORE_ASSERT(false,errorLog);
			return;
		}
		glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, glm::value_ptr(value));
	}

	void OpenGLShader::UploadData(std::string name, const float& value)
	{
		GLint uniformLocation = GetUniformLocation(name);
		
		if (uniformLocation == -1)
		{
			std::string errorLog = "Not able to upload float data to location named " + name;
			ZERO_CORE_ASSERT(false, errorLog);
			return;
		}
		glUniform1f(uniformLocation, value);
	}

	void OpenGLShader::UploadData(std::string name, const int& value)
	{
		GLint uniformLocation = GetUniformLocation(name);

		if (uniformLocation == -1)
		{
			std::string errorLog = "Not able to upload int data to location named " + name;
			ZERO_CORE_ASSERT(false, errorLog);
			return;
		}
		glUniform1i(uniformLocation, value);
	}

	void OpenGLShader::UploadData(std::string name, const glm::vec4& value)
	{
		GLint uniformLocation = GetUniformLocation(name);

		if (uniformLocation == -1)
		{
			std::string errorLog = "Not able to upload vec4 data to location named " + name;
			ZERO_CORE_ASSERT(false,name);
			return;
		}
		glUniform4f(uniformLocation, value.x, value.y, value.z, value.w);
	}

	void OpenGLShader::UploadData(std::string name, const glm::vec3& value)
	{
		GLint uniformLocation = GetUniformLocation(name);

		if (uniformLocation == -1)
		{
			std::string errorLog = "Not able to upload vec3 data to location named " + name;
			ZERO_CORE_ASSERT(false, errorLog);
			return;
		}

		glUniform3f(uniformLocation, value.x, value.y, value.z);
	}

	GLint OpenGLShader::GetUniformLocation(std::string name)
	{
		return glGetUniformLocation(m_RendererID, name.c_str());
	}


	OpenGLShader::~OpenGLShader()
	{
		glDeleteProgram(m_RendererID);
	}

}