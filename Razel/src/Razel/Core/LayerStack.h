#pragma once

#include "Razel/Core/Base.h"
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
		std::vector<Layer*>::reverse_iterator rbegin() { return m_Layers.rbegin(); }
		std::vector<Layer*>::reverse_iterator rend() { return m_Layers.rend(); }

		std::vector<Layer*>::const_iterator begin() const { return m_Layers.begin(); }
		std::vector<Layer*>::const_iterator end() const { return m_Layers.end(); }
		std::vector<Layer*>::const_reverse_iterator rbegin()const { return m_Layers.rbegin(); }
		std::vector<Layer*>::const_reverse_iterator rend() const { return m_Layers.rend(); }

	private:
		std::vector<Layer*> m_Layers;					// 存储层栈的所有层指针
		//std::vector<Layer*>::iterator m_LayerInsert;	// 指向当前栈中应该插入新层的位置（普通层和叠加层的分界线）--迭代器失效
		unsigned int m_LayerInsertIndex = 0;			// 指向当前栈中应该插入新层的位置（普通层和叠加层的分界线）
	};
}

