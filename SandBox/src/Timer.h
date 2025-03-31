#pragma once
#include <chrono>
#include <iostream>
#include <vector>
// ��׼����
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
	// ���������� Timer ���������������ʱ�����Զ����� Stop() ������ֹͣ��ʱ�����ʱ������
	~Timer()
	{
		if (!m_Stopped)
			Stop();
	}
	// Stop �������ڼ���� Timer ���󴴽����˷���ִ�е�ʱ�����ѽ������� std::cout��
	void Stop()
	{
		// ֹͣ��ʱ��
		auto endTimepoint = std::chrono::high_resolution_clock::now();
		// ��ȡ��ʼ�ͽ�����ʱ��㣨��λ����s��
		long long start = std::chrono::time_point_cast<std::chrono::microseconds>(m_StartTimepoint).time_since_epoch().count();
		long long end = std::chrono::time_point_cast<std::chrono::microseconds>(endTimepoint).time_since_epoch().count();
		
		m_Stopped = true;

		// ���������ʱ��ͺ���
		float duration = (end - start) * 0.001f;
		
		m_Func({ m_Name,duration });

	}
private:
	// ��Ա���������ڴ洢��ʼ��ʱ��㡣
	const char* m_Name;
	Fn m_Func;
	std::chrono::time_point<std::chrono::steady_clock> m_StartTimepoint;
	bool m_Stopped;
};