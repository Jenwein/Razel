#pragma once

#include <memory>

#include "Razel/Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

namespace Razel
{
	class RAZEL_API Log
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }

	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};

}

// Core log macros
#define RZ_CORE_TRACE(...) ::Razel::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define RZ_CORE_INFO(...) ::Razel::Log::GetCoreLogger()->info(__VA_ARGS__)
#define RZ_CORE_WARN(...) ::Razel::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define RZ_CORE_ERROR(...) ::Razel::Log::GetCoreLogger()->error(__VA_ARGS__)
#define RZ_CORE_CRITICAL(...) ::Razel::Log::GetCoreLogger()->critical(__VA_ARGS__)
// Client log macros
#define RZ_TRACE(...) ::Razel::Log::GetClientLogger()->trace(__VA_ARGS__)
#define RZ_INFO(...) ::Razel::Log::GetClientLogger()->info(__VA_ARGS__)
#define RZ_WARN(...) ::Razel::Log::GetClientLogger()->warn(__VA_ARGS__)
#define RZ_ERROR(...) ::Razel::Log::GetClientLogger()->error(__VA_ARGS__)
#define RZ_CRITICAL(...) ::Razel::Log::GetClientLogger()->critical(__VA_ARGS__)