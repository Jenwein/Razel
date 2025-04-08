#include "rzpch.h"
#include "Window.h"

#ifdef RZ_PLATFORM_WINDOWS
	#include "Platform/Windows/WindowsWindow.h"
#endif // RZ_PLATFORM_WINDOWS

namespace Razel
{
	Scope<Window> Window::Create(const WindowProps& props)
	{
#ifdef RZ_PLATFORM_WINDOWS
		return CreateScope<WindowsWindow>(props);
#else
		RZ_CORE_ASSERT(false, "Unknown platform!");
		return nullptr;								// ���ڷ���nullptr֮ǰ�����ϵ�
#endif
	}


}
