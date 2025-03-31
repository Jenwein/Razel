#include "rzpch.h"

#include "Log.h"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace Razel
{
	// 初始化静态成员
	std::shared_ptr<spdlog::logger> Log::s_CoreLogger;
	std::shared_ptr<spdlog::logger> Log::s_ClientLogger;

	void Log::Init()
	{
		// 设置日志模式
		spdlog::set_pattern("%^[%T] %n: %v%$");

		s_CoreLogger = spdlog::stdout_color_mt("RAZEL");
		s_CoreLogger->set_level(spdlog::level::trace);

		s_ClientLogger = spdlog::stdout_color_mt("app");
		s_ClientLogger ->set_level(spdlog::level::trace);
	}

}
