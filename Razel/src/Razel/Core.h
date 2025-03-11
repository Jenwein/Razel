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

// ��1����xλ�õ����������룬�����������¼������Կ����ù�'|'��'&'���в�ͬ���¼�����
#define BIT(x) (1 << x)