#pragma once
#include "Event.h"


namespace Zero
{
	class ZERO_API MouseMovedEvent : public Event
	{
	

	public:
		MouseMovedEvent(float mouseX, float mouseY) : m_MouseX(mouseX), m_MouseY(mouseY) {}

		inline float GetMouseX() { return m_MouseX; }
		inline float GetMouseY() { return m_MouseY; }

		std::string ToString() const override
		{
			std::stringstream stream;
			stream << "MouseMoved : (" << m_MouseX << " , " << m_MouseY << " )";
			return stream.str();
		}
		EVENT_CLASS_CATEGORY(EventCategoryMouse);
		EVENT_CLASS_TYPE(MouseMoved);
	
	private:
		float m_MouseX;
		float m_MouseY;
	};
}
