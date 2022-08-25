#pragma once

#include<string>
#include "Zero/Renderer/Texture.h"

namespace Zero
{
	class OpenGLTexture2D : public Texture2D
	{
	public:
		OpenGLTexture2D(const std::string& filePath,const uint32_t& textureSlot);
		virtual void Bind() override;
		virtual void Unbind() override;
		virtual void SetTextureSlot(const uint32_t& textureSlot) override;
		virtual int GetWidth() const override { return m_Width; }
		virtual int GetHeight() const override { return m_Height;}
		~OpenGLTexture2D();

	private:
		uint32_t m_RendererID;
		int m_Width;
		int m_Height;
	};
}
