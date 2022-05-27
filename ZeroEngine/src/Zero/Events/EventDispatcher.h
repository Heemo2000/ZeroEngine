#pragma once
#include "../Core.h"
#include "Event.h"
namespace Zero
{
	class ZERO_API EventDispatcher
	{
	private:
		Event& m_Event;
	public:
		EventDispatcher(Event& event) : m_Event(event)
		{

		}
		template<typename T>
		bool Dispatch(std::function<bool(T&)> func)
		{
			if (m_Event.GetEventType() == T::GetStaticType())
			{
				m_Event.m_Handled = func(*(T*)&m_Event);
				return true;
			}

			return false;
		}
	};
}
