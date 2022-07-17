#pragma once
#include "Zero/Window.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Platform/OpenGL/OpenGLRenderingContext.h"
namespace Zero
{

	
	class WindowsWindow : public Window
	{
	public:
		WindowsWindow(const WindowProps& props);
		virtual ~WindowsWindow();

		inline unsigned int GetWidth() const override { return m_Data.Width; }
		inline unsigned int GetHeight() const override { return m_Data.Height; }
		inline virtual void* GetNativeWindow() const override{ return (void*)m_Window; }
		inline void SetEventCallback(const EventCallbackFn& callback) override { m_Data.EventCallback = callback; }

		void OnUpdate() override;
		bool IsVsync() const override;
		void SetVsync(bool enabled) override;

	private:
		struct WindowsData
		{
			std::string Title;

			unsigned int Width;
			unsigned int Height;
			bool Vsync;

			EventCallbackFn EventCallback;
		};
	
	private:
		GLFWwindow* m_Window;
		WindowsData m_Data;
		OpenGLRenderingContext* m_Context;
	private:
		void Init(const WindowProps& props);
		void Shutdown();
	};
}


