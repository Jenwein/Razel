#pragma once

#include "Razel/Core/Core.h"
#include "Razel/Core/Layer.h"

#include <vector>

namespace Razel
{
	class LayerStack
	{
		// |--------------------层栈--------------------------|
		// | 普通层栈 (Layer Stack) | 叠加层栈 (Overlay Stack) |
	public:
		LayerStack() = default;
		~LayerStack();

		void PushLayer(Layer* layer);			// 添加普通层
		void PushOverLayer(Layer* overlayer);	// 添加叠加层
		void PopLayer(Layer* layer);			// 移除普通层
		void PopOverLayer(Layer* overlayer);	// 移除叠加层

		std::vector<Layer*>::iterator begin() { return m_Layers.begin(); }
		std::vector<Layer*>::iterator end() { return m_Layers.end(); }

	private:
		std::vector<Layer*> m_Layers;					// 存储层栈的所有层指针
		//std::vector<Layer*>::iterator m_LayerInsert;	// 指向当前栈中应该插入新层的位置（普通层和叠加层的分界线）--迭代器失效
		unsigned int m_LayerInsertIndex = 0;			// 指向当前栈中应该插入新层的位置（普通层和叠加层的分界线）
	};
}

