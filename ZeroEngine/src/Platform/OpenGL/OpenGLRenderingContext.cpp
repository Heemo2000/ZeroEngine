#include "zeropch.h"
#include "OpenGLRenderingContext.h"
namespace Zero
{
	OpenGLRenderingContext::OpenGLRenderingContext(GLFWwindow* windowHandle) : m_WindowHandle(windowHandle) 
	{
		ZERO_CORE_ASSERT(windowHandle, "Window handle is null!!");
	}

	void OpenGLRenderingContext::Init()
	{
		glfwMakeContextCurrent(m_WindowHandle);
		int glLoaded = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		ZERO_CORE_ASSERT(glLoaded, "Could not load OpenGL functions!");
		
		ZERO_CORE_INFO("OpenGL version : {0}", glGetString(GL_VERSION));
	}

	void OpenGLRenderingContext::SwapBuffers()
	{
		glfwSwapBuffers(m_WindowHandle);
	}
}