#include "zeropch.h"
#include "OpenGLFramebuffer.h"

namespace Zero
{
	OpenGLFramebuffer::OpenGLFramebuffer(const FramebufferSpecification& spec)
	{
		m_Spec = spec;
		glCreateFramebuffers(1, &m_RendererID);
		glBindFramebuffer(GL_FRAMEBUFFER, m_RendererID);

		GLenum internalFormat = GL_RGBA8;
		GLenum dataFormat = GL_RGBA;
		glGenTextures(1, &m_TargetTexture);
		glBindTexture(GL_TEXTURE_2D, m_TargetTexture);
		glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, spec.Width, spec.Height, 0, dataFormat,GL_UNSIGNED_BYTE, NULL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	void OpenGLFramebuffer::Invalidate()
	{
		glBindTexture(GL_TEXTURE_2D, m_TargetTexture);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + m_Spec.ColorAttachment, GL_TEXTURE_2D,m_TargetTexture, 0);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	

	void OpenGLFramebuffer::Bind()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, m_RendererID);
		//glReadBuffer(GL_COLOR_ATTACHMENT0 + m_Spec.ColorAttachment);
		glViewport(0, 0, m_Spec.Width, m_Spec.Height);
	}

	void OpenGLFramebuffer::Unbind()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	uint32_t OpenGLFramebuffer::GetFramebufferTexID() const
	{
		return m_TargetTexture;
	}
	OpenGLFramebuffer::~OpenGLFramebuffer()
	{
		glDeleteFramebuffers(1, &m_RendererID);
	}
}