#pragma once
#include <glad/glad.h>
#include "Zero/Renderer/Framebuffer.h"
#include "Platform/OpenGL/OpenGLTexture2D.h"

namespace Zero
{
	class OpenGLFramebuffer : public Framebuffer
	{
	 public:
		 OpenGLFramebuffer(const FramebufferSpecification& spec);
		 void virtual Invalidate() override;
		 void virtual Bind() override;
		 void virtual Unbind() override;
		 uint32_t virtual GetFramebufferTexID() const override;
		 ~OpenGLFramebuffer();

	 private:
		 uint32_t m_RendererID;
		 uint32_t m_TargetTexture;

	};
}
