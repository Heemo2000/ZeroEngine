#include "zeropch.h"
#include "Application.h"
#include "Events/ApplicationEvent.h"
#include "Log.h"
namespace Zero
{
	Application::Application()
	{

	}

	Application::~Application()
	{

	}

	void Application::Run()
	{
		Zero::WindowResizedEvent event(1280, 720);

		if (event.IsInCategory(Zero::EventCategory::EventCategoryApplication))
		{
			ZERO_CORE_TRACE(event.ToString());
		}

		while (true);
	}
}
