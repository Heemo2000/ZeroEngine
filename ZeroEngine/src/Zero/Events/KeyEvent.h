#pragma once
#include "Event.h"

namespace Zero
{
	class ZERO_API KeyEvent : public Event
	{
	
	public:
		inline int GetKeyCode() const { return m_KeyCode; }

		EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput);
	
	protected:
		KeyEvent(int keyCode) : m_KeyCode(keyCode) {}

	private:
		int m_KeyCode;
	};

	class ZERO_API KeyPressedEvent : public KeyEvent
	{
	public:
		KeyPressedEvent(int keyCode, int repeatCount) : KeyEvent(keyCode), m_RepeatCount(repeatCount) {}

		inline int GetRepeatCount() { return m_RepeatCount; }
		
		std::string ToString() const override
		{
			std::stringstream stream;
			stream << "KeyPressed(" << KeyEvent::GetKeyCode() << ") : " << m_RepeatCount << " key repeats";
			return stream.str();
		}

		EVENT_CLASS_TYPE(KeyPressed);

	private:
		int m_RepeatCount;
	};

	class ZERO_API KeyReleasedEvent : public KeyEvent
	{
	public:
		KeyReleasedEvent(int keyCode) : KeyEvent(keyCode) {}

		std::string ToString() const override
		{
			std::stringstream stream;
			stream << "KeyReleased(" << KeyEvent::GetKeyCode() << ")";
			return stream.str();
		}

		EVENT_CLASS_TYPE(KeyReleased);
	};

	class ZERO_API KeyTypedEvent : public KeyEvent
	{
	public:
		KeyTypedEvent(int keyCode) : KeyEvent(keyCode) {}

		std::string ToString() const override
		{
			std::stringstream stream;
			stream << "KeyTyped(" << KeyEvent::GetKeyCode() << ")";
			return stream.str();
		}

		EVENT_CLASS_TYPE(KeyTyped);
	};
}
