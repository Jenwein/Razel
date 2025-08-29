#include "rzpch.h"
#include "UUID.h"

#include <random>
#include <unordered_map>

namespace Razel
{
	static std::random_device s_RandomDevice;								// 随机数种子
	static std::mt19937_64 s_Engine(s_RandomDevice());						// 梅森旋转算法随机数生成器
	static std::uniform_int_distribution<uint64_t> s_UniformDistribution;	// 随机数

	UUID::UUID()
		:m_UUID(s_UniformDistribution(s_Engine))
	{
	}

	UUID::UUID(uint64_t uuid)
		:m_UUID(uuid)
	{
	}
}
