#pragma once
#include <string>
#include <chrono>
#include <algorithm>
#include <fstream>
#include <thread>

namespace Razel
{
	// 单次性能分析结果
	struct ProfileResult
	{
		std::string Name;		// 代码段名称
		long long Start, End;	// 代码段的起止时间
		uint32_t ThreadID;		// 线程ID
	};

	// 当前的分析会话
	struct InstrumentationSession
	{
		std::string Name;		// 当前会话的名称
	};

	// 管理性能分析的整个生命周期
	class Instrumentor
	{
	private:
		InstrumentationSession* m_CurrentSession;	// 当前会话
		std::ofstream m_OutputStream;				// 输出文件流
		int m_ProfileCount;							// 记录的Profile数量

	public:
		Instrumentor()
			:m_CurrentSession(nullptr),m_ProfileCount(0)
		{
		}

		// 开始会话
		void BeginSession(const std::string& name, const std::string& filepath = "result.json")
		{
			m_OutputStream.open(filepath);
			WriteHeader();
			m_CurrentSession = new InstrumentationSession{name};
		}

		// 结束会话
		void EndSession()
		{
			WriteFooter();
			m_OutputStream.close();
			delete m_CurrentSession;
			m_CurrentSession = nullptr;
			m_ProfileCount = 0;
		}

		//写入数据：
		//"dur"：执行时间（End - Start）
		//"tid"：线程 ID。
		//"ts"：起始时间戳。
		void WriteProfile(const ProfileResult& result)
		{
			if (m_ProfileCount++ > 0)
				m_OutputStream << ",";

			std::string name = result.Name;
			std::replace(name.begin(), name.end(), '"', '\'');

			m_OutputStream << "{";
			m_OutputStream << "\"cat\":\"function\",";
			m_OutputStream << "\"dur\":" << (result.End - result.Start) << ',';
			m_OutputStream << "\"name\":\"" << name << "\",";
			m_OutputStream << "\"ph\":\"X\",";
			m_OutputStream << "\"pid\":0,";
			m_OutputStream << "\"tid\":" << result.ThreadID << ",";
			m_OutputStream << "\"ts\":" << result.Start;
			m_OutputStream << "}";

			m_OutputStream.flush();
		}
		void WriteHeader()
		{
			m_OutputStream << "{\"otherData\": {},\"traceEvents\":[";
			m_OutputStream.flush();
		}
		void WriteFooter()
		{
			m_OutputStream << "]}";
			m_OutputStream.flush();
		}

		static Instrumentor& Get()
		{
			static Instrumentor instance;
			return instance;
		}

	};
	// 计时器类，用于测量代码段的执行时间
	class InstrumentationTimer
	{
	public:
		InstrumentationTimer(const char* name)
			:m_Name(name), m_Stopped(false)
		{
			m_StartTimepoint = std::chrono::high_resolution_clock::now();
		}

		~InstrumentationTimer()
		{
			if (!m_Stopped)
				Stop();
		}

		void Stop()
		{
			auto endTimepoint = std::chrono::high_resolution_clock::now();
			long long start = std::chrono::time_point_cast<std::chrono::microseconds>(m_StartTimepoint).time_since_epoch().count();
			long long end = std::chrono::time_point_cast<std::chrono::microseconds>(endTimepoint).time_since_epoch().count();

			uint32_t threadID = std::hash<std::thread::id>{}(std::this_thread::get_id());
			Instrumentor::Get().WriteProfile({ m_Name,start,end,threadID });

			m_Stopped = true;
		}


	private:
		const char* m_Name;
		std::chrono::time_point <std::chrono::high_resolution_clock> m_StartTimepoint;
		bool m_Stopped;
	};
}

#define RZ_PROFILE 1		// 启用性能分析 (1/0)
#if RZ_PROFILE
#define RZ_PROFILE_BEGIN_SESSION(name, filepath) ::Razel::Instrumentor::Get().BeginSession(name, filepath)	// 开始分析会话
#define RZ_PROFILE_END_SESSION() ::Razel::Instrumentor::Get().EndSession()									// 结束会话
#define RZ_PROFILE_SCOPE(name) ::Razel::InstrumentationTimer timer##__LINE__(name);							// 定义局部作用域的分析器，用 __LINE__ 保证变量唯一性
#define RZ_PROFILE_FUNCTION() RZ_PROFILE_SCOPE(__FUNCSIG__)													// 自动获取当前函数名进行分析
#else
#define RZ_PROFILE_BEGIN_SESSION(name, filepath)
#define RZ_PROFILE_END_SESSION()
#define RZ_PROFILE_SCOPE(name)
#define RZ_PROFILE_FUNCTION()
#endif