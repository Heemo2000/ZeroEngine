#pragma once
#include "Event.h"
#include<sstream>

namespace Zero
{
	class ZERO_API WindowResizedEvent : public Event
	{
	private:
		unsigned int m_Width;
		unsigned int m_Height;

	public:
		WindowResizedEvent(unsigned int width, unsigned int height) : m_Width(width),m_Height(height) {}
		inline unsigned int GetWidth() const { return m_Width; }
		inline unsigned int GetHeight() const { return m_Height; }

		std::string ToString() const override
		{
			std::stringstream stream;
			stream << "Window Resized : Width = " << m_Width << " , Height = " << m_Height;
			return stream.str();
		}
		EVENT_CLASS_TYPE(WindowResized);
		EVENT_CLASS_CATEGORY(EventCategoryApplication);
	};

	class ZERO_API WindowClosedEvent : public Event
	{
	
	public:
		
		EVENT_CLASS_TYPE(WindowClosed);
		EVENT_CLASS_CATEGORY(EventCategoryApplication);
	};

	class ZERO_API WindowFocusedEvent : public Event
	{

	public:

		EVENT_CLASS_TYPE(WindowFocused);
		EVENT_CLASS_CATEGORY(EventCategoryApplication);
	};

	class ZERO_API WindowLostFocusEvent : public Event
	{

	public:

		EVENT_CLASS_TYPE(WindowLostFocus);
		EVENT_CLASS_CATEGORY(EventCategoryApplication);
	};

	class ZERO_API AppTickEvent : public Event
	{

	public:

		EVENT_CLASS_TYPE(AppTick);
		EVENT_CLASS_CATEGORY(EventCategoryApplication);
	};

	class ZERO_API AppRenderEvent : public Event
	{
	public:

		EVENT_CLASS_TYPE(AppRender);
		EVENT_CLASS_CATEGORY(EventCategoryApplication);
	};
}
