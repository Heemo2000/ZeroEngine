#pragma once
#include<zeropch.h>
#include "Core.h"
#include "Events/Event.h"


namespace Zero
{
	struct WindowProps
	{
		std::string Title;
		unsigned int Width;
		unsigned int Height;

		WindowProps(const std::string& title = "Zero Engine", unsigned int width = 1336, unsigned int height = 768)
			: Title(title), Width(width) , Height(height) {}

	};

	class ZERO_API Window
	{
	public:
		using EventCallbackFn = std::function<void(Event&)>;

		virtual ~Window() {};
		virtual unsigned int GetWidth() const = 0;
		virtual unsigned int GetHeight() const = 0;
		virtual void* GetNativeWindow() const = 0;

		virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
		virtual bool IsVsync() const = 0;
		virtual void SetVsync(bool enabled) = 0;

		virtual void OnUpdate() = 0;
		static Window* Create(const WindowProps& props = WindowProps());

	};
}