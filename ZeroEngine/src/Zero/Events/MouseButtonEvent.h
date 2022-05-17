#pragma once
#include "Event.h"
#include<sstream>

namespace Zero
{
	class ZERO_API MouseButtonEvent : public Event
	{
	protected:
		int m_Button;
	public:
		MouseButtonEvent(int button) : m_Button(button) {}

		inline int GetMouseButton() { return m_Button; }

		EVENT_CLASS_CATEGORY(EventCategoryMouseButton);
	};

	class ZERO_API MouseButtonClickedEvent : public MouseButtonEvent
	{

	public:
		MouseButtonClickedEvent(int button) : MouseButtonEvent(button) {}


		std::string ToString() const override
		{
			std::stringstream stream;
			stream << "Mouse Clicked : " << m_Button;
			return stream.str();
		}

		EVENT_CLASS_TYPE(MouseClicked);
	};
}
