#pragma once
#include <string>

namespace Razel
{
	class FileDialogs 
	{
	public:
		// ����Ѿ�ȡ�����򷵻ؿ��ַ���
		static std::string OpenFile(const char* filter);
		static std::string SaveFile(const char* filter);
	};
}
