#pragma once

#include "Razel/Core.h"
#include "Events/Event.h"

namespace Razel {

	class RAZEL_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
	};

	// To be defined in CLIENT
	Application* CreateApplication();

}