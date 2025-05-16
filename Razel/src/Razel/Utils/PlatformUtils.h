#pragma once
#include <string>
#include <optional>

namespace Razel
{
	class FileDialogs 
	{
	public:
		// ����Ѿ�ȡ�����򷵻ؿ��ַ���
		static std::optional<std::string> OpenFile(const char* filter);
		static std::optional<std::string> SaveFile(const char* filter);
	};
}
