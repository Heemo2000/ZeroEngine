#pragma once
#include <string>


namespace Zero
{
	//Should add ZERO_API macro in the future.
	class ZERO_API Texture
	{
	public:
		virtual int GetWidth() const = 0;
		virtual int GetHeight() const = 0;
		~Texture() {}
	};

	class ZERO_API Texture2D : Texture
	{
	public:
		static Texture2D* Create(const std::string& filePath, const uint32_t& textureSlot);
		virtual void Bind() = 0;
		virtual void Unbind() = 0;
		virtual void SetTextureSlot(const uint32_t& textureSlot) = 0;
	};

}