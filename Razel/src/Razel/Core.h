#pragma once

#ifdef RZ_PLATFORM_WINDOWS
	#ifdef RZ_BUILD_DLL
		#define RAZEL_API __declspec(dllexport)
	#else
		#define RAZEL_API __declspec(dllimport)
	#endif
#else
	#error RAZEL only supports Windows!
#endif

// 将1左移x位得到二进制掩码，以用来分类事件，可以快速用过'|'或'&'进行不同的事件操作
#define BIT(x) (1 << x)