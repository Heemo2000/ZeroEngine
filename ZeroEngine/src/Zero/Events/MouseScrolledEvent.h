#pragma once
#include "Event.h"

namespace Zero
{
	class ZERO_API MouseScrolledEvent : public Event
	{
	
	public:
		MouseScrolledEvent(float scrolledX, float scrolledY) : m_ScrolledX(scrolledX), m_ScrolledY(scrolledY) {}

		inline float GetScrolledX() const { return m_ScrolledX; }
		inline float GetScrolledY() const { return m_ScrolledY; }

		std::string ToString() const override
		{
			std::stringstream stream;
			stream << "MouseScrolled : " << m_ScrolledX << " , " << m_ScrolledY;
			return stream.str();
		}

		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput);
		EVENT_CLASS_TYPE(MouseScrolled);

	private:
		float m_ScrolledX;
		float m_ScrolledY;
	};
}
