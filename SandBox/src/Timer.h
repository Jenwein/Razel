#pragma once
#include <chrono>
#include <iostream>
#include <vector>
// 基准测试
#define PROFILE_SCOPE(name) Timer timer##__LINE__(name,[&](ProfileResult profileResult){m_ProfileResults.push_back(profileResult);})

struct ProfileResult
{
	const char* Name;
	float Time;
};

std::vector<ProfileResult> m_ProfileResults;

template<typename Fn>
class Timer
{
public:
	Timer(const char* name, Fn&& func)
		:m_Name(name), m_Func(func), m_Stopped(false)
	{
		m_StartTimepoint = std::chrono::high_resolution_clock::now();
	}
	// 析构函数在 Timer 对象结束生命周期时，会自动触发 Stop() 方法，停止计时并输出时间结果。
	~Timer()
	{
		if (!m_Stopped)
			Stop();
	}
	// Stop 方法用于计算从 Timer 对象创建到此方法执行的时间差，并把结果输出到 std::cout。
	void Stop()
	{
		// 停止计时点
		auto endTimepoint = std::chrono::high_resolution_clock::now();
		// 获取开始和结束的时间点（单位：μs）
		long long start = std::chrono::time_point_cast<std::chrono::microseconds>(m_StartTimepoint).time_since_epoch().count();
		long long end = std::chrono::time_point_cast<std::chrono::microseconds>(endTimepoint).time_since_epoch().count();
		
		m_Stopped = true;

		// 计算持续的时间和毫秒
		float duration = (end - start) * 0.001f;
		
		m_Func({ m_Name,duration });

	}
private:
	// 成员变量，用于存储开始的时间点。
	const char* m_Name;
	Fn m_Func;
	std::chrono::time_point<std::chrono::steady_clock> m_StartTimepoint;
	bool m_Stopped;
};