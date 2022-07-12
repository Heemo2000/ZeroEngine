#pragma once
#include <string>


namespace Zero
{
	class ZERO_API Shader
	{
	public:

		static Shader* Create(const std::string& vertexSource, const std::string& fragmentSource);
		virtual void Bind() = 0;
		virtual void UnBind() = 0;

		~Shader() {};
	};
}

