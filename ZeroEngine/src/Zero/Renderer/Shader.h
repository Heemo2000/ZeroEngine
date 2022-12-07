#pragma once
#include <string>
#include <glm/glm.hpp>

namespace Zero
{
	class ZERO_API Shader
	{
	public:

		static Zero::Ref<Shader> Create(const std::string& filePath);
		static Zero::Ref<Shader> Create(const std::string& name,const std::string& vertexSource, const std::string& fragmentSource);
		virtual std::string GetName() const = 0;
		virtual void Bind() = 0;
		virtual void UnBind() = 0;
		virtual void UploadData(std::string name,const glm::mat4& value) = 0;
		virtual void UploadData(std::string name, const float& value) = 0;
		virtual void UploadData(std::string name, const int& value) = 0;
		virtual void UploadData(std::string name, const glm::vec4& value) = 0;
		virtual void UploadData(std::string name, const glm::vec3& value) = 0;

		~Shader() {};
	};


	class ZERO_API ShaderLibrary
	{
	public:
		void Add(const std::string& name,const Zero::Ref<Zero::Shader>& shader);
		void Add(const Zero::Ref<Zero::Shader>& shader);
		Zero::Ref<Shader> Load(const std::string& filePath);
		Zero::Ref<Shader> Load(const std::string& name, const std::string& filePath);
		Zero::Ref<Shader> Get(const  std::string& name);
	private:
		std::unordered_map<std::string,Zero::Ref<Zero::Shader>> m_Shaders;
	};
}

