#pragma once
#include<zeropch.h>
#include "Zero/Core.h"

namespace Zero
{
	enum class EventType
	{
		None = 0,
		WindowResized,
		WindowClosed,
		WindowFocused,
		WindowLostFocus,
		KeyPressed,
		KeyReleased,
		KeyTyped,
		MouseMoved,
		MouseButtonClicked,
		MouseButtonReleased,
		MouseScrolled,
		AppTick,
		AppRender
	};

	enum EventCategory
	{
		None = 0,
		EventCategoryApplication = BIT(0),
		EventCategoryInput		 = BIT(1),
		EventCategoryKeyboard	 = BIT(2),
		EventCategoryMouse		 = BIT(3),
		EventCategoryMouseButton = BIT(4)
	};


#define EVENT_CLASS_TYPE(type) static EventType GetStaticType() {return EventType::##type;}\
							   virtual EventType GetEventType() const override { return GetStaticType(); }\
							   virtual const char* GetName() const override { return #type;}


#define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const override { return category;}

	class ZERO_API Event
	{
	public:
		bool Handled = false;
	public:
		virtual EventType GetEventType() const = 0;
		virtual int GetCategoryFlags() const = 0;
		virtual const char* GetName() const = 0;
		virtual std::string ToString() const { return GetName(); }

		inline bool IsInCategory(EventCategory category)
		{
			return GetCategoryFlags() & category;
		}
	};
	

	inline std::ostream& operator <<(std::ostream& stream, const Event& event)
	{
		return stream << event.ToString();
	}
}


