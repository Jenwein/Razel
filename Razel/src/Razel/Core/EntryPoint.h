#pragma once
#ifdef RZ_PLATFORM_WINDOWS

extern Razel::Application* Razel::CreateApplication();

int main(int argc, char** argv)
{
	Razel::Log::Init();

	RZ_CORE_INFO("Hello");

	auto app = Razel::CreateApplication();
	app->Run();
	delete app;
}

#endif