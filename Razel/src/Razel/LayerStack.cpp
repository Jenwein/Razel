#include "rzpch.h"
#include "LayerStack.h"

namespace Razel
{
	LayerStack::LayerStack()
	{
	}

	LayerStack::~LayerStack()
	{
		for (Layer* layer:m_Layers)
		{
			delete layer;
		}
	}

	void LayerStack::PushLayer(Layer* layer)
	{
		// 将layer添加在m_LayerInsert位置，并更新m_LayerInsert 
		m_Layers.emplace(m_Layers.begin() + m_LayerInsertIndex, layer);
		m_LayerInsertIndex++;
	}

	void LayerStack::PushOverLayer(Layer* overlayer)
	{
		m_Layers.emplace_back(overlayer);

	}
	// 查找要移除的层的位置，移除层并更新m_LayerInsert
	void LayerStack::PopLayer(Layer* layer)
	{
		auto it =  std::find(m_Layers.begin(), m_Layers.end(), layer);
		
		if (it != m_Layers.end())
		{
			m_Layers.erase(it);
			m_LayerInsertIndex--;
		}
	}

	void LayerStack::PopOverLayer(Layer* overlayer)
	{
		auto it = std::find(m_Layers.begin(), m_Layers.end(), overlayer);

		if (it != m_Layers.end())
		{
			m_Layers.erase(it);
		}
	}

}