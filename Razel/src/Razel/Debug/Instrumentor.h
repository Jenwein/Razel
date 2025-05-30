#pragma once

#include <algorithm>
#include <chrono>
#include <fstream>
#include <iomanip>
#include <string>
#include <thread>
#include <mutex>
#include <sstream>

#include "Razel/Core/Log.h"

namespace Razel
{
	using FloatingPointMicroseconds = std::chrono::duration<double, std::micro>;

	// 单次性能分析结果
	struct ProfileResult
	{
		std::string Name;		// 代码段名称
		FloatingPointMicroseconds Start;
		std::chrono::microseconds ElapsedTime;
		std::thread::id ThreadID;		// 线程ID
	};

	// 当前的分析会话
	struct InstrumentationSession
	{
		std::string Name;		// 当前会话的名称
	};

	// 管理性能分析的整个生命周期
	class Instrumentor
	{
	public:
		Instrumentor(const Instrumentor&) = delete;
		Instrumentor(Instrumentor&&) = delete;

		// 开始会话
		void BeginSession(const std::string& name, const std::string& filepath = "result.json")
		{
			std::lock_guard lock(m_Mutex);
			if (m_CurrentSession) 
			{
				// If there is already a current session, then close it before beginning new one.
				// Subsequent profiling output meant for the original session will end up in the
				// newly opened session instead.  That's better than having badly formatted
				// profiling output.
				if (Log::GetCoreLogger()) 
				{ 
					// Edge case: BeginSession() might be before Log::Init()
					RZ_CORE_ERROR("Instrumentor::BeginSession('{0}') when session '{1}' already open.", name, m_CurrentSession->Name);
				}
				InternalEndSession();
			}
			m_OutputStream.open(filepath);

			if (m_OutputStream.is_open())
			{
				m_CurrentSession = new InstrumentationSession({ name });
				WriteHeader();
			}
			else 
			{
				if (Log::GetCoreLogger()) 
				{ // Edge case: BeginSession() might be before Log::Init()
					RZ_CORE_ERROR("Instrumentor could not open results file '{0}'.", filepath);
				}
			}
		}

		// 结束会话
		void EndSession()
		{
			std::lock_guard lock(m_Mutex);
			InternalEndSession();
		}

		//写入数据：
		//"dur"：执行时间（End - Start）
		//"tid"：线程 ID。
		//"ts"：起始时间戳。
		void WriteProfile(const ProfileResult& result)
		{
			std::stringstream json;

			json << std::setprecision(3) << std::fixed;
			json << ",{";
			json << "\"cat\":\"function\",";
			json << "\"dur\":" << (result.ElapsedTime.count()) << ',';
			json << "\"name\":\"" << result.Name << "\",";
			json << "\"ph\":\"X\",";
			json << "\"pid\":0,";
			json << "\"tid\":" << result.ThreadID << ",";
			json << "\"ts\":" << result.Start.count();
			json << "}";

			std::lock_guard lock(m_Mutex);
			if (m_CurrentSession) 
			{
				m_OutputStream << json.str();
				m_OutputStream.flush();
			}
		}

		static Instrumentor& Get() {
			static Instrumentor instance;
			return instance;
		}
	private:
		Instrumentor()
			: m_CurrentSession(nullptr)
		{
		}

		~Instrumentor()
		{
			EndSession();
		}
		void WriteHeader()
		{
			m_OutputStream << "{\"otherData\": {},\"traceEvents\":[{}";
			m_OutputStream.flush();
		}
		void WriteFooter()
		{
			m_OutputStream << "]}";
			m_OutputStream.flush();
		}

		// Note: you must already own lock on m_Mutex before
		// calling InternalEndSession()
		void InternalEndSession() 
		{
			if (m_CurrentSession) 
			{
				WriteFooter();
				m_OutputStream.close();
				delete m_CurrentSession;
				m_CurrentSession = nullptr;
			}
		}

	private:
		std::mutex m_Mutex;
		InstrumentationSession* m_CurrentSession;
		std::ofstream m_OutputStream;

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
			auto endTimepoint = std::chrono::steady_clock::now();
			auto highResStart = FloatingPointMicroseconds{ m_StartTimepoint.time_since_epoch() };
			auto elapsedTime = std::chrono::time_point_cast<std::chrono::microseconds>(endTimepoint).time_since_epoch() - std::chrono::time_point_cast<std::chrono::microseconds>(m_StartTimepoint).time_since_epoch();

			Instrumentor::Get().WriteProfile({ m_Name, highResStart, elapsedTime, std::this_thread::get_id() });

			m_Stopped = true;
		}


	private:
		const char* m_Name;
		std::chrono::time_point<std::chrono::steady_clock> m_StartTimepoint;
		bool m_Stopped;
	};
	namespace InstrumentorUtils {

		template <size_t N>
		struct ChangeResult
		{
			char Data[N];
		};

		template <size_t N, size_t K>
		constexpr auto CleanupOutputString(const char(&expr)[N], const char(&remove)[K])
		{
			ChangeResult<N> result = {};

			size_t srcIndex = 0;
			size_t dstIndex = 0;
			while (srcIndex < N)
			{
				size_t matchIndex = 0;
				while (matchIndex < K - 1 && srcIndex + matchIndex < N - 1 && expr[srcIndex + matchIndex] == remove[matchIndex])
					matchIndex++;
				if (matchIndex == K - 1)
					srcIndex += matchIndex;
				result.Data[dstIndex++] = expr[srcIndex] == '"' ? '\'' : expr[srcIndex];
				srcIndex++;
			}
			return result;
		}
	}
}

#define RZ_PROFILE 0		// 启用性能分析 (1/0)
#if RZ_PROFILE

// Resolve which function signature macro will be used. Note that this only
// is resolved when the (pre)compiler starts, so the syntax highlighting
// could mark the wrong one in your editor!
#if defined(__GNUC__) || (defined(__MWERKS__) && (__MWERKS__ >= 0x3000)) || (defined(__ICC) && (__ICC >= 600)) || defined(__ghs__) 1Has a conversation.
#define RZ_FUNC_SIG __PRETTY_FUNCTION__
#elif defined(__DMC__) && (__DMC__ >= 0x810)
#define RZ_FUNC_SIG __PRETTY_FUNCTION__
#elif (defined(__FUNCSIG__) || (_MSC_VER))
#define RZ_FUNC_SIG __FUNCSIG__
#elif (defined(__INTEL_COMPILER) && (__INTEL_COMPILER >= 600)) || (defined(__IBMCPP__) && (__IBMCPP__ >= 500))
#define RZ_FUNC_SIG __FUNCTION__
#elif defined(__BORLANDC__) && (__BORLANDC__ >= 0x550)
#define RZ_FUNC_SIG __FUNC__
#elif defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 199901)
#define RZ_FUNC_SIG __func__
#elif defined(__cplusplus) && (__cplusplus >= 201103)
#define RZ_FUNC_SIG __func__
#else
#define RZ_FUNC_SIG "RZ_FUNC_SIG unknown!"
#endif

#define RZ_PROFILE_BEGIN_SESSION(name, filepath) ::Razel::Instrumentor::Get().BeginSession(name, filepath)	// 开始分析会话
#define RZ_PROFILE_END_SESSION() ::Razel::Instrumentor::Get().EndSession()									// 结束会话
#define RZ_PROFILE_SCOPE_LINE2(name, line) constexpr auto fixedName##line = ::Razel::InstrumentorUtils::CleanupOutputString(name, "__cdecl ");\
											   ::Razel::InstrumentationTimer timer##line(fixedName##line.Data)
#define RZ_PROFILE_SCOPE_LINE(name, line) RZ_PROFILE_SCOPE_LINE2(name, line)
#define RZ_PROFILE_SCOPE(name) RZ_PROFILE_SCOPE_LINE(name, __LINE__)
#define RZ_PROFILE_FUNCTION() RZ_PROFILE_SCOPE(__FUNCSIG__)													// 自动获取当前函数名进行分析
#else
#define RZ_PROFILE_BEGIN_SESSION(name, filepath)
#define RZ_PROFILE_END_SESSION()
#define RZ_PROFILE_SCOPE(name)
#define RZ_PROFILE_FUNCTION()
#endif