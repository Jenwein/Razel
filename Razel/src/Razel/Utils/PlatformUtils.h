#pragma once
#include <string>

namespace Razel
{
	class FileDialogs 
	{
	public:
		// 如果已经取消，则返回空字符串
		static std::string OpenFile(const char* filter);
		static std::string SaveFile(const char* filter);
	};
}
