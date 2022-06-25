#pragma once

#include "Zero/Renderer/RenderingContext.h"
#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace Zero
{
	class OpenGLRenderingContext : public RenderingContext
	{
	public:
		OpenGLRenderingContext(GLFWwindow* windowHandle);
		virtual void Init() override;
		virtual void SwapBuffers() override;
	private:
		GLFWwindow* m_WindowHandle;
	};
}
