#include "zeropch.h"
#include "WindowsWindow.h"

namespace Zero
{
	static bool s_GLFWInitialized = false;
	
	static void GLFWErrorCallback(int error,const char* description)
	{
		ZERO_CORE_ERROR("GLFWError({0}) : {1}", error, description);
	}
	
	Window* Window::Create(const WindowProps& props)
	{
		return new WindowsWindow(props);
	}
	WindowsWindow::WindowsWindow(const WindowProps& props)
	{
		Init(props);
	}

	WindowsWindow::~WindowsWindow()
	{
		Shutdown();
	}

	void WindowsWindow::Init(const WindowProps& props)
	{
		m_Data.Title = props.Title;
		m_Data.Width = props.Width;
		m_Data.Height = props.Height;
		
		ZERO_CORE_INFO("Creating window {0} ({1}, {2})", props.Title, props.Width, props.Height);
		if (!s_GLFWInitialized)
		{
			int success = glfwInit();
			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);

			ZERO_CORE_ASSERT(success, "Could not initialize GLFW!");
			glfwSetErrorCallback(GLFWErrorCallback);
			s_GLFWInitialized = true;
		}

		m_Window = glfwCreateWindow((int)m_Data.Width, (int)m_Data.Height, m_Data.Title.c_str(), NULL, NULL);
		glfwMakeContextCurrent(m_Window);
		int glLoaded = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

		ZERO_CORE_ASSERT(glLoaded, "Could not load OpenGL functions!");
		
		glfwSetWindowUserPointer(m_Window, &m_Data);
		SetVsync(true);

		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window) 
		{
			WindowsData data = *(WindowsData*)glfwGetWindowUserPointer(window);
			
			WindowClosedEvent event;

			data.EventCallback(event);
		});

		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window,int width,int height)
		{
			WindowsData data = *(WindowsData*)glfwGetWindowUserPointer(window);

			WindowResizedEvent event(width, height);

			data.EventCallback(event);
		});


		glfwSetKeyCallback(m_Window, [](GLFWwindow* window,int keyCode,int scanCode,int action,int mods)
		{
			WindowsData& data = *(WindowsData*)glfwGetWindowUserPointer(window);

			switch (action)
			{
				case GLFW_PRESS:
								{
									KeyPressedEvent pressedEvent(keyCode, 0);
									data.EventCallback(pressedEvent);
								}
								break;
				case GLFW_RELEASE:
								{
									KeyReleasedEvent releasedEvent(keyCode);
									data.EventCallback(releasedEvent);
								}
								break;
			}
		});

		glfwSetCharCallback(m_Window, [](GLFWwindow* window, unsigned int keyCode) 
			{
				WindowsData& data = *(WindowsData*)glfwGetWindowUserPointer(window);
				KeyTypedEvent typedEvent(keyCode);

				data.EventCallback(typedEvent);
			});

		glfwSetMouseButtonCallback(m_Window,[](GLFWwindow* window, int keyCode, int action, int mods)
			{
				WindowsData& data = *(WindowsData*)glfwGetWindowUserPointer(window);

				switch (action)
				{
					case GLFW_PRESS:
									{
										MouseButtonClickedEvent clickedEvent(keyCode);
										data.EventCallback(clickedEvent);
									}
									break;

					case GLFW_RELEASE:
									{
										MouseButtonReleasedEvent releasedEvent(keyCode);
										data.EventCallback(releasedEvent);
									}
									break;
				}
			});

		glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xPos,double yPos)
		{
			WindowsData& data = *(WindowsData*)glfwGetWindowUserPointer(window);

			MouseMovedEvent event((float)xPos, (float)yPos);
			data.EventCallback(event);
		});

		glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xOffSet, double yOffSet)
		{
			WindowsData& data = *(WindowsData*)glfwGetWindowUserPointer(window);
			
			MouseScrolledEvent event((float)xOffSet, (float)yOffSet);
			data.EventCallback(event);
		});
	}

	void WindowsWindow::Shutdown()
	{
		glfwDestroyWindow(m_Window);
	}

	void WindowsWindow::OnUpdate()
	{
		glfwPollEvents();
		glfwSwapBuffers(m_Window);
	}

	bool WindowsWindow::IsVsync() const
	{
		return m_Data.Vsync;
	}

	void WindowsWindow::SetVsync(bool enabled)
	{
		if (enabled)
		{
			glfwSwapInterval(1);
		}
		else
		{
			glfwSwapInterval(0);
		}

		m_Data.Vsync = enabled;
	}
}