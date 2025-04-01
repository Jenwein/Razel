#pragma once
#include <string>
#include <chrono>
#include <algorithm>
#include <fstream>
#include <thread>

namespace Razel
{
	// �������ܷ������
	struct ProfileResult
	{
		std::string Name;		// ���������
		long long Start, End;	// ����ε���ֹʱ��
		uint32_t ThreadID;		// �߳�ID
	};

	// ��ǰ�ķ����Ự
	struct InstrumentationSession
	{
		std::string Name;		// ��ǰ�Ự������
	};

	// �������ܷ�����������������
	class Instrumentor
	{
	private:
		InstrumentationSession* m_CurrentSession;	// ��ǰ�Ự
		std::ofstream m_OutputStream;				// ����ļ���
		int m_ProfileCount;							// ��¼��Profile����

	public:
		Instrumentor()
			:m_CurrentSession(nullptr),m_ProfileCount(0)
		{
		}

		// ��ʼ�Ự
		void BeginSession(const std::string& name, const std::string& filepath = "result.json")
		{
			m_OutputStream.open(filepath);
			WriteHeader();
			m_CurrentSession = new InstrumentationSession{name};
		}

		// �����Ự
		void EndSession()
		{
			WriteFooter();
			m_OutputStream.close();
			delete m_CurrentSession;
			m_CurrentSession = nullptr;
			m_ProfileCount = 0;
		}

		//д�����ݣ�
		//"dur"��ִ��ʱ�䣨End - Start��
		//"tid"���߳� ID��
		//"ts"����ʼʱ�����
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
	// ��ʱ���࣬���ڲ�������ε�ִ��ʱ��
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

#define RZ_PROFILE 1		// �������ܷ��� (1/0)
#if RZ_PROFILE
#define RZ_PROFILE_BEGIN_SESSION(name, filepath) ::Razel::Instrumentor::Get().BeginSession(name, filepath)	// ��ʼ�����Ự
#define RZ_PROFILE_END_SESSION() ::Razel::Instrumentor::Get().EndSession()									// �����Ự
#define RZ_PROFILE_SCOPE(name) ::Razel::InstrumentationTimer timer##__LINE__(name);							// ����ֲ�������ķ��������� __LINE__ ��֤����Ψһ��
#define RZ_PROFILE_FUNCTION() RZ_PROFILE_SCOPE(__FUNCSIG__)													// �Զ���ȡ��ǰ���������з���
#else
#define RZ_PROFILE_BEGIN_SESSION(name, filepath)
#define RZ_PROFILE_END_SESSION()
#define RZ_PROFILE_SCOPE(name)
#define RZ_PROFILE_FUNCTION()
#endif