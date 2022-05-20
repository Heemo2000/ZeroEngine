#pragma once
#include "Event.h"

namespace Zero
{
	class ZERO_API KeyEvent : public Event
	{
	private:
		int m_KeyCode;

	protected:
		KeyEvent(int keyCode) : m_KeyCode(keyCode) {}

	public:
		inline int GetKeyCode() { return m_KeyCode; }

		EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput);
	};

	class ZERO_API KeyPressedEvent : public KeyEvent
	{
	private:
		int m_RepeatCount;
	public:
		KeyPressedEvent(int keyCode, int repeatCount) : KeyEvent(keyCode), m_RepeatCount(repeatCount) {}

		inline int GetRepeatCount() { return m_RepeatCount; }
		
		std::string ToString() const override
		{
			
			std::stringstream stream;
			stream << "KeyPressed : " << m_RepeatCount << " key repeats";
			return stream.str();
		}

		EVENT_CLASS_TYPE(KeyPressed);
	};

	class ZERO_API KeyReleasedEvent : public KeyEvent
	{
	public:
		KeyReleasedEvent(int keyCode) : KeyEvent(keyCode) {}

		EVENT_CLASS_TYPE(KeyReleased);
	};
}
