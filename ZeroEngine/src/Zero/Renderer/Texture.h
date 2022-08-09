#pragma once
#include <string>


namespace Zero
{
	//Should add ZERO_API macro in the future.
	class Texture
	{
	public:
		static Texture* Create(std::string& filePath, uint32_t textureSlot);
		virtual void Bind() = 0;
		virtual void Unbind() = 0;
		virtual void SetTextureSlot(uint32_t textureSlot) = 0;
		~Texture() {}
	};

}