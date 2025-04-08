#include "rzpch.h"
#include "Input.h"

#ifdef RZ_PLATFORM_WINDOWS
	#include "Platform/Windows/WindowsInput.h"
#endif // RZ_PLATFORM_WINDOWS


namespace Razel
{
	Scope<Input> Input::s_Instance = Input::Create();

	Scope<Input> Input::Create()
	{
#ifdef RZ_PLATFORM_WINDOWS
		return CreateScope<WindowsInput>();
#elif define(RZ_PLATFORM_LINUX)
		//return CreateScope<LinuxInput>();
#else
		RZ_CORE_ASSERT(false, "Unknown platform!");
		return nullptr; 
#endif
	}

}