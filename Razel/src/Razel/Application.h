#pragma once

#include "Razel/Core.h"
#include "Events/Event.h"
#include "Window.h"
namespace Razel {

	class RAZEL_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
	private:
		std::unique_ptr<Window>m_Window;
		bool m_Running = true;

	};

	// To be defined in CLIENT
	Application* CreateApplication();

}