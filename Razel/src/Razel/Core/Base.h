#pragma once
#include <memory>

#include "Razel/Core/PlatformDetection.h"

#ifdef RZ_DEBUG
	#if defined(RZ_PLATFORM_WINDOWS)
		#define RZ_DEBUGBREAK() __debugbreak()
	#elif defined(RZ_PLATFORM_LINUX)
		#include <signal.h>
		#define RZ_DEBUGBREAK() raise(SIGTRAP)
	#else
		#error "Platform doesn't support debugbreak yet!"
	#endif
	#define RZ_ENABLE_ASSERTS
#else
	#define RZ_DEBUGBREAK()
#endif

#define RZ_EXPAND_MACRO(x) x
#define RZ_STRINGIFY_MACRO(x) #x

//#define  BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)
#define BIND_EVENT_FN(fn) [this](auto&&... args) -> decltype(auto) { return this->fn(std::forward<decltype(args)>(args)...); }
// ��1����xλ�õ����������룬�����������¼������Կ����ù�'|'��'&'���в�ͬ���¼�����
#define BIT(x) (1 << x)


namespace Razel
{
	template<typename T>
	using Scope = std::unique_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Scope<T> CreateScope(Args&& ... args)
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}

	template<typename T>
	using Ref = std::shared_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Ref<T> CreateRef(Args&& ... args)
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}
}


#include "Razel/Core/Log.h"
#include "Razel/Core/Assert.h"