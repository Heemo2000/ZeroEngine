#pragma once

#include<string>
#include "Zero/Renderer/Texture.h"

namespace Zero
{
	class OpenGLTexture : public Texture
	{
	public:
		OpenGLTexture(const std::string& filePath,const uint32_t& textureSlot);
		virtual void Bind() override;
		virtual void Unbind() override;
		virtual void SetTextureSlot(uint32_t textureSlot) override;
		~OpenGLTexture();

	private:
		uint32_t m_RendererID;
	};
}
