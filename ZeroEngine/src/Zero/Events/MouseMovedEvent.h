#pragma once
#include "Event.h"
#include<sstream>

namespace Zero
{
	class ZERO_API MouseMovedEvent : public Event
	{
	private:
		float m_MouseX;
		float m_MouseY;

	public:
		MouseMovedEvent(float mouseX, float mouseY) : m_MouseX(mouseX), m_MouseY(mouseY) {}

		inline float GetMouseX() { return m_MouseX; }
		inline float GetMouseY() { return m_MouseY; }

		std::string ToString() const override
		{
			std::stringstream stream;
			stream << "Mouse Moved : (" << m_MouseX << " , " << m_MouseY << " )" << std::endl;
		}
		EVENT_CLASS_CATEGORY(EventCategoryMouse);
		EVENT_CLASS_TYPE(MouseMoved);
	};
}
