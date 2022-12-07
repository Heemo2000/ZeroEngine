#include "zeropch.h"
#include "OpenGLShader.h"
#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>
#include "Zero/Utility/FileContentsReader.h"

namespace Zero
{
	GLenum OpenGLShader::ShaderTypeFromString(const std::string& type)
	{
		if (type == "vertex")
			return GL_VERTEX_SHADER;
		if (type == "fragment" || type == "pixel")
			return GL_FRAGMENT_SHADER;

		ZERO_CORE_ASSERT(false, "Unknown shader type!");
		return 0;
	}

	OpenGLShader::OpenGLShader(const std::string& filePath)
	{
		std::string shaderFileContents = GetFileContents(filePath);
		
		auto shaderSources = PreProcess(shaderFileContents);
		Compile(shaderSources);

		auto lastSlashPos = filePath.find_last_of("/\\");
		int fileNameStartIndex = (lastSlashPos != std::string::npos) ? lastSlashPos + 1 : 0;
		int dotIndex = filePath.rfind(".");
		int fileNameLastIndex = (dotIndex != -1) ? dotIndex - 1 : filePath.size() - 1;
		int fileNameSize = fileNameLastIndex - fileNameStartIndex + 1;

		m_Name = filePath.substr(fileNameStartIndex, fileNameSize);
	}
	OpenGLShader::OpenGLShader(const std::string& name,const std::string& vertexSource, const std::string& fragmentSource) : m_Name(name)
	{
		std::unordered_map<GLenum, std::string> shaderSources;
		shaderSources[GL_VERTEX_SHADER] = vertexSource;
		shaderSources[GL_FRAGMENT_SHADER] = fragmentSource;
		Compile(shaderSources);
	}

	std::string OpenGLShader::GetName() const
	{
		return m_Name;
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

	std::unordered_map<GLenum, std::string> OpenGLShader::PreProcess(const std::string& source)
	{
		std::unordered_map<GLenum, std::string> shaderSources;
		const char* typeToken = "#type";
		size_t typeTokenLength = strlen(typeToken);
		size_t pos = source.find(typeToken, 0);
		while (pos != std::string::npos)
		{
			size_t eol = source.find_first_of("\r\n", pos);
			ZERO_CORE_ASSERT(eol != std::string::npos, "Syntax error");
			size_t begin = pos + typeTokenLength + 1;
			std::string type = source.substr(begin, eol - begin);
			ZERO_CORE_ASSERT(ShaderTypeFromString(type), "Invalid shader type specified");

			size_t nextLinePos = source.find_first_not_of("\r\n", eol);
			pos = source.find(typeToken, nextLinePos);
			shaderSources[ShaderTypeFromString(type)] = source.substr(nextLinePos, pos - (nextLinePos == std::string::npos ? source.size() - 1 : nextLinePos));
		}

		return shaderSources;

	}

	void OpenGLShader::Compile(const std::unordered_map<GLenum, std::string> shaderSources)
	{
		GLuint program = glCreateProgram();
		std::vector<GLuint> createdShaders;
		for (auto i = shaderSources.begin(); i != shaderSources.end(); i++)
		{
			GLenum shaderType = i->first;
			const GLchar* shaderSource = i->second.c_str();
			GLuint shader = glCreateShader(shaderType);
			glShaderSource(shader, 1, &shaderSource, NULL);
			glCompileShader(shader);

			GLint compileSuccess;
			glGetShaderiv(shader, GL_COMPILE_STATUS, &compileSuccess);

			if (!compileSuccess)
			{
				GLint logLength = 0;
				glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logLength);
				std::vector<GLchar> infoLog(logLength);
				glGetShaderInfoLog(shader, logLength, &logLength, &infoLog[0]);

				glDeleteShader(shader);
				ZERO_CORE_ERROR("{0}", infoLog);
				ZERO_CORE_ASSERT(false, "Shader compilation failure!!");
				return;
			}

			glAttachShader(program, shader);
			createdShaders.push_back(shader);
		}
		
		m_RendererID = program;
		glLinkProgram(program);

		GLint isLinked = 0;
		glGetProgramiv(program, GL_LINK_STATUS, (int*)&isLinked);
		if (isLinked == GL_FALSE)
		{
			GLint infoLength = 0;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLength);

			std::vector<GLchar> infoLog(infoLength);
			glGetProgramInfoLog(program, infoLength, &infoLength, &infoLog[0]);

			glDeleteProgram(program);
			
			for (int i = 0; i < createdShaders.size(); i++)
			{
				glDeleteShader(createdShaders[i]);
			}
			ZERO_CORE_ERROR("{0}", infoLog);
			ZERO_CORE_ASSERT(false, "Shader program Linking failed!!");
			return;
		}

		for (int i = 0; i < createdShaders.size(); i++)
		{
			glDetachShader(program,createdShaders[i]);
		}	
	}

	OpenGLShader::~OpenGLShader()
	{
		glDeleteProgram(m_RendererID);
	}

	
}