#pragma once
#include <string>
#include <glm/glm.hpp>

namespace Zero
{
	class ZERO_API Shader
	{
	public:

		static Shader* Create(const std::string& vertexSource, const std::string& fragmentSource);
		virtual void Bind() = 0;
		virtual void UnBind() = 0;
		virtual void UploadData(std::string name,const glm::mat4& value) = 0;
		virtual void UploadData(std::string name, const float& value) = 0;
		virtual void UploadData(std::string name, const int& value) = 0;
		virtual void UploadData(std::string name, const glm::vec4& value) = 0;
		virtual void UploadData(std::string name, const glm::vec3& value) = 0;

		~Shader() {};
	};
}

