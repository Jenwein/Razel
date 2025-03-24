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
		// ��layer�����m_LayerInsertλ�ã�������m_LayerInsert 
		m_Layers.emplace(m_Layers.begin() + m_LayerInsertIndex, layer);
		layer->OnAttach();
		m_LayerInsertIndex++;
	}

	void LayerStack::PushOverLayer(Layer* overlayer)
	{
		m_Layers.emplace_back(overlayer);
		overlayer->OnAttach();
	}
	// ����Ҫ�Ƴ��Ĳ��λ�ã��Ƴ��㲢����m_LayerInsert
	void LayerStack::PopLayer(Layer* layer)
	{
		auto it =  std::find(m_Layers.begin(), m_Layers.end(), layer);
		layer->OnDetach();
		if (it != m_Layers.end())
		{
			m_Layers.erase(it);
			m_LayerInsertIndex--;
		}
	}

	void LayerStack::PopOverLayer(Layer* overlayer)
	{
		auto it = std::find(m_Layers.begin(), m_Layers.end(), overlayer);
		overlayer->OnDetach();
		if (it != m_Layers.end())
		{
			m_Layers.erase(it);
		}
	}

}