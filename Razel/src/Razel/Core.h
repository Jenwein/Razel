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

#ifdef RZ_DEBUG
	#define RZ_ENABLE_ASSERTS
#endif // RZ_DEBUG



#ifdef RZ_ENABLE_ASSERTS
	#define  RZ_ASSERT(x,...) {if(!(x)){RZ_ERROR("Assertion Failed: {0}",__VA_ARGS__);__debugbreak();}}
	#define  RZ_CORE_ASSERT(x,...){if(!(x)){RZ_CORE_ERROR("Assertion Failed: {0}",__VA_ARGS__);__debugbreak();}}
#else
	#define RZ_ASSERT(x,...)
	#define RZ_CORE_ASSERT(x,...)
#endif

#define  BIND_EVENT_FN(x) std::bind(&x,this,std::placeholders::_1)

// 将1左移x位得到二进制掩码，以用来分类事件，可以快速用过'|'或'&'进行不同的事件操作
#define BIT(x) (1 << x)