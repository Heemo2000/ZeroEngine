#pragma once
//#include "zeropch.h"

#include "Zero/Events/ApplicationEvent.h"
#include "Zero/Events/KeyEvent.h"
#include "Zero/Events/MouseButtonEvent.h"
#include "Zero/Events/MouseMovedEvent.h"
#include "Zero/Events/MouseScrolledEvent.h"

#include "Zero/Window.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
namespace Zero
{

	
	class WindowsWindow : public Window
	{
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
		
		
		void Init(const WindowProps& props);
		void Shutdown();

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

	};
}


