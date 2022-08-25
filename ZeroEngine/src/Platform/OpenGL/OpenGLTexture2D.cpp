#include "zeropch.h"
#include <glad/glad.h>
#include <stb_image.h>
#include "Platform/OpenGL/OpenGLTexture2D.h"

namespace Zero
{
	OpenGLTexture2D::OpenGLTexture2D(const std::string& filePath,const uint32_t& textureSlot)
	{
		int width, height, channels;

		stbi_set_flip_vertically_on_load(1);
		unsigned char* imageData = stbi_load(filePath.c_str(), &width, &height, &channels, 4);

		m_Width = width;
		m_Height = height;

		if (!imageData)
		{
			ZERO_CORE_ASSERT(false, "Image loading failed!!");
			return;
		}

		GLenum internalFormat = 0;
		GLenum dataFormat = 0;
		if (channels == 4)
		{
			internalFormat = GL_RGBA8;
			dataFormat = GL_RGBA;
		}
		else if (channels == 3)
		{
			internalFormat = GL_RGB8;
			dataFormat = GL_RGB;
		}

		ZERO_CORE_ASSERT(internalFormat & dataFormat, "Format not supported!!");

		//Now, generate texture.
		glGenTextures(1, &m_RendererID);
		glActiveTexture(GL_TEXTURE0 + textureSlot);
		glBindTexture(GL_TEXTURE_2D, m_RendererID);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);


		glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, dataFormat, GL_UNSIGNED_BYTE, imageData);
		glGenerateMipmap(GL_TEXTURE_2D);
		stbi_image_free(imageData);

		glActiveTexture(GL_TEXTURE0 + textureSlot);
	}

	void OpenGLTexture2D::Bind()
	{
		glBindTexture(GL_TEXTURE_2D, m_RendererID);
	}

	void OpenGLTexture2D::Unbind()
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	void OpenGLTexture2D::SetTextureSlot(const uint32_t& textureSlot)
	{
		glActiveTexture(GL_TEXTURE0 + textureSlot);
	}

	OpenGLTexture2D::~OpenGLTexture2D()
	{
		glDeleteTextures(1, &m_RendererID);
	}
}

