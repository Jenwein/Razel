#pragma once
#include "Razel/Core/Core.h"

#ifdef RZ_PLATFORM_WINDOWS

extern Razel::Application* Razel::CreateApplication();

int main(int argc, char** argv)
{
	Razel::Log::Init();

	RZ_PROFILE_BEGIN_SESSION("Startup", "HazelProfile-Startup.json");
	auto app = Razel::CreateApplication();
	RZ_PROFILE_END_SESSION();

	RZ_PROFILE_BEGIN_SESSION("Runtime", "HazelProfile-Runtime.json");
	app->Run();
	RZ_PROFILE_END_SESSION();


	RZ_PROFILE_BEGIN_SESSION("Shutdown", "HazelProfile-Shutdown.json");
	delete app;
	RZ_PROFILE_END_SESSION();
}

#endif