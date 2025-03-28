#pragma once
#include <memory>
#ifdef RZ_PLATFORM_WINDOWS
#if RZ_DYNAMIC_LINK
	#ifdef RZ_BUILD_DLL
		#define RAZEL_API __declspec(dllexport)
	#else
		#define RAZEL_API __declspec(dllimport)
	#endif
#else
	#define RAZEL_API
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

//#define  BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)
#define BIND_EVENT_FN(fn) [this](auto& e) { return this->fn(e); }
// 将1左移x位得到二进制掩码，以用来分类事件，可以快速用过'|'或'&'进行不同的事件操作
#define BIT(x) (1 << x)


namespace Razel
{
	template<typename T>
	using Scope = std::unique_ptr<T>;

	template<typename T>
	using Ref = std::shared_ptr<T>;

}

