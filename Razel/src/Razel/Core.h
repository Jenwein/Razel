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

// ��1����xλ�õ����������룬�����������¼������Կ����ù�'|'��'&'���в�ͬ���¼�����
#define BIT(x) (1 << x)