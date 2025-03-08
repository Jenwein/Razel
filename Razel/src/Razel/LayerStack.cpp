#include "rzpch.h"
#include "LayerStack.h"

namespace Razel
{
	LayerStack::LayerStack()
	{
		m_LayerInsert = m_Layers.begin();
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
		// ��layer�����m_LayerInsertλ�ã�������m_LayerInsert 
		m_LayerInsert = m_Layers.emplace(m_LayerInsert, layer);
	}

	void LayerStack::PushOverLayer(Layer* overlayer)
	{
		m_Layers.emplace_back(overlayer);

	}
	// ����Ҫ�Ƴ��Ĳ��λ�ã��Ƴ��㲢����m_LayerInsert
	void LayerStack::PopLayer(Layer* layer)
	{
		auto it =  std::find(m_Layers.begin(), m_Layers.end(), layer);
		
		if (it != m_Layers.end())
		{
			m_Layers.erase(it);
			m_LayerInsert--;
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