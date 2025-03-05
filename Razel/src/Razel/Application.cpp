#include "rzpch.h"

#include "Application.h"

#include "Razel/Log.h"
#include "Razel/Events/ApplicationEvent.h"
namespace Razel {

	Application::Application()
	{

	}

	Application::~Application()
	{

	}

	void Application::Run()
	{
		WindowResizeEvent e(1280,780);
		if (e.IsInCategory(EventCategoryApplication))
		{
			RZ_TRACE(e.GetName());
		}
		if (e.IsInCategory(EventCategoryInput))
		{
			RZ_TRACE(e.GetName());
		}
		while (true);
	}

}