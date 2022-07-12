#include "zeropch.h"
#include "OpenGLShader.h"
#include <glad/glad.h>

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
			glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &logLength);
			std::vector<GLchar> infoLog(logLength);
			glGetShaderInfoLog(fragmentShader, logLength, &logLength, &infoLog[0]);
			glDeleteShader(fragmentShader);

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
			// Use the infoLog as you see fit.
			
			// In this simple program, we'll just leave
			return;
		}

		glDetachShader(m_RendererID, fragmentShader);
		glDetachShader(m_RendererID, vertexShader);
	}

	void OpenGLShader::Bind()
	{
		glUseProgram(m_RendererID);
	}

	void OpenGLShader::UnBind()
	{
		glUseProgram(0);
	}


	OpenGLShader::~OpenGLShader()
	{
		glDeleteProgram(m_RendererID);
	}

}