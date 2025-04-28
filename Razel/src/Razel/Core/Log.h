#pragma once

#include "Razel/Core/Base.h"


// This ignores all warnings raised inside External headers
#pragma warning(push, 0)
#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>
#pragma warning(pop)
namespace Razel
{
	class Log
	{
	public:
		static void Init();

		static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }

	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};

}

// Core log macros 引擎内部代码的日志记录
#define RZ_CORE_TRACE(...) ::Razel::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define RZ_CORE_INFO(...) ::Razel::Log::GetCoreLogger()->info(__VA_ARGS__)
#define RZ_CORE_WARN(...) ::Razel::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define RZ_CORE_ERROR(...) ::Razel::Log::GetCoreLogger()->error(__VA_ARGS__)
#define RZ_CORE_CRITICAL(...) ::Razel::Log::GetCoreLogger()->critical(__VA_ARGS__)
// Client log macros 用于应用程序代码的日志记录
#define RZ_TRACE(...) ::Razel::Log::GetClientLogger()->trace(__VA_ARGS__)
#define RZ_INFO(...) ::Razel::Log::GetClientLogger()->info(__VA_ARGS__)
#define RZ_WARN(...) ::Razel::Log::GetClientLogger()->warn(__VA_ARGS__)
#define RZ_ERROR(...) ::Razel::Log::GetClientLogger()->error(__VA_ARGS__)
#define RZ_CRITICAL(...) ::Razel::Log::GetClientLogger()->critical(__VA_ARGS__)