#pragma once
#ifdef RZ_PLATFORM_WINDOWS

extern Razel::Application* Razel::CreateApplication();

int main(int argc, char** argv)
{
	Razel::Log::Init();

	RZ_CORE_INFO("Hello");
	int i = 5;
	RZ_WARN("Vale = {0}",i);

	auto app = Razel::CreateApplication();
	app->Run();
	delete app;
}

#endif