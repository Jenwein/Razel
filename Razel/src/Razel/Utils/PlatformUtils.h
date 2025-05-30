#pragma once
#include <string>
#include <optional>

namespace Razel
{
	class FileDialogs 
	{
	public:
		// 如果已经取消，则返回空字符串
		static std::optional<std::string> OpenFile(const char* filter);
		static std::optional<std::string> SaveFile(const char* filter);
	};
}
