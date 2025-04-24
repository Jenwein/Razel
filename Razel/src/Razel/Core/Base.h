#pragma once
#include <memory>


// Platform detection using predefined macros
#ifdef _WIN32
	/* Windows x64/x86 */
	#ifdef _WIN64
	/* Windows x64  */
		#define RZ_PLATFORM_WINDOWS
	#else
		/* Windows x86 */
		#error "x86 Builds are not supported!"
	#endif
#elif defined(__APPLE__) || defined(__MACH__)
	#include <TargetConditionals.h>
	/* TARGET_OS_MAC exists on all the platforms
	 * so we must check all of them (in this order)
	 * to ensure that we're running on MAC
	 * and not some other Apple platform */
	#if TARGET_IPHONE_SIMULATOR == 1
		#error "IOS simulator is not supported!"
	#elif TARGET_OS_IPHONE == 1
		#define RZ_PLATFORM_IOS
		#error "IOS is not supported!"
	#elif TARGET_OS_MAC == 1
		#define RZ_PLATFORM_MACOS
		#error "MacOS is not supported!"
	#else
		#error "Unknown Apple platform!"
	#endif
/* We also have to check __ANDROID__ before __linux__
 * since android is based on the linux kernel
 * it has __linux__ defined */
#elif defined(__ANDROID__)
	#define RZ_PLATFORM_ANDROID
	#error "Android is not supported!"
#elif defined(__linux__)
	#define RZ_PLATFORM_LINUX
	#error "Linux is not supported!"
#else
	/* Unknown compiler/platform */
	#error "Unknown platform!"
#endif // End of platform detection


// DLL support
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
#endif // End of DLL support

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

#ifdef RZ_ENABLE_ASSERTS
	#define RZ_ASSERT(x, ...) { if(!(x)) { RZ_ERROR("Assertion Failed: {0}", __VA_ARGS__); RZ_DEBUGBREAK(); } }
	#define RZ_CORE_ASSERT(x, ...) { if(!(x)) { RZ_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); RZ_DEBUGBREAK(); } }
#else
	#define RZ_ASSERT(x, ...)
	#define RZ_CORE_ASSERT(x, ...)
#endif

//#define  BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)
#define BIND_EVENT_FN(fn) [this](auto&&... args) -> decltype(auto) { return this->fn(std::forward<decltype(args)>(args)...); }
// 将1左移x位得到二进制掩码，以用来分类事件，可以快速用过'|'或'&'进行不同的事件操作
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

