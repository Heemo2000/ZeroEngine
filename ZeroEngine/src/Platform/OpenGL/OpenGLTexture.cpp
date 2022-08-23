#include "zeropch.h"

#include <glad/glad.h>
#include <stb_image.h>
#include "Platform/OpenGL/OpenGLTexture.h"

namespace Zero
{
	OpenGLTexture::OpenGLTexture(const std::string& filePath,const uint32_t& textureSlot)
	{
		int width, height, components;

		stbi_set_flip_vertically_on_load(1);
		unsigned char* imageData = stbi_load(filePath.c_str(), &width, &height, &components, 4);

		if (!imageData)
		{
			ZERO_CORE_ASSERT(false, "Image loading failed!!");
			return;
		}

		//Now, generate texture.
		glGenTextures(1, &m_RendererID);
		glActiveTexture(GL_TEXTURE0 + textureSlot);
		glBindTexture(GL_TEXTURE_2D, m_RendererID);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);
		glGenerateMipmap(GL_TEXTURE_2D);
		stbi_image_free(imageData);

		glActiveTexture(GL_TEXTURE0 + textureSlot);
	}

	void OpenGLTexture::Bind()
	{
		glBindTexture(GL_TEXTURE_2D, m_RendererID);
	}

	void OpenGLTexture::Unbind()
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	void OpenGLTexture::SetTextureSlot(uint32_t textureSlot)
	{
		glActiveTexture(GL_TEXTURE0 + textureSlot);
	}

	OpenGLTexture::~OpenGLTexture()
	{
		glDeleteTextures(1, &m_RendererID);
	}
}

