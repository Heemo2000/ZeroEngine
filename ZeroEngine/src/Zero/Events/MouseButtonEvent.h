#pragma once
#include "Event.h"

namespace Zero
{
	class ZERO_API MouseButtonEvent : public Event
	{
	
	public:
		MouseButtonEvent(int button) : m_Button(button) {}

		inline int GetMouseButton() { return m_Button; }

		EVENT_CLASS_CATEGORY(EventCategoryMouseButton);
	protected:
		int m_Button;
	
	};

	class ZERO_API MouseButtonClickedEvent : public MouseButtonEvent
	{

	public:
		MouseButtonClickedEvent(int button) : MouseButtonEvent(button) {}


		std::string ToString() const override
		{
			std::stringstream stream;
			stream << "MouseButtonClicked : " << m_Button;
			return stream.str();
		}

		EVENT_CLASS_TYPE(MouseButtonClicked);
	};

	class ZERO_API MouseButtonReleasedEvent : public MouseButtonEvent
	{

	public:
		MouseButtonReleasedEvent(int button) : MouseButtonEvent(button) {}


		std::string ToString() const override
		{
			std::stringstream stream;
			stream << "MouseButtonReleased : " << m_Button;
			return stream.str();
		}

		EVENT_CLASS_TYPE(MouseButtonReleased);
	};


}
