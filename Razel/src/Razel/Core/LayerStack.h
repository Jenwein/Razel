#pragma once

#include "Razel/Core/Core.h"
#include "Razel/Core/Layer.h"

#include <vector>

namespace Razel
{
	class LayerStack
	{
		// |--------------------��ջ--------------------------|
		// | ��ͨ��ջ (Layer Stack) | ���Ӳ�ջ (Overlay Stack) |
	public:
		LayerStack() = default;
		~LayerStack();

		void PushLayer(Layer* layer);			// �����ͨ��
		void PushOverLayer(Layer* overlayer);	// ��ӵ��Ӳ�
		void PopLayer(Layer* layer);			// �Ƴ���ͨ��
		void PopOverLayer(Layer* overlayer);	// �Ƴ����Ӳ�

		std::vector<Layer*>::iterator begin() { return m_Layers.begin(); }
		std::vector<Layer*>::iterator end() { return m_Layers.end(); }
		std::vector<Layer*>::reverse_iterator rbegin() { return m_Layers.rbegin(); }
		std::vector<Layer*>::reverse_iterator rend() { return m_Layers.rend(); }

		std::vector<Layer*>::const_iterator begin() const { return m_Layers.begin(); }
		std::vector<Layer*>::const_iterator end() const { return m_Layers.end(); }
		std::vector<Layer*>::const_reverse_iterator rbegin()const { return m_Layers.rbegin(); }
		std::vector<Layer*>::const_reverse_iterator rend() const { return m_Layers.rend(); }

	private:
		std::vector<Layer*> m_Layers;					// �洢��ջ�����в�ָ��
		//std::vector<Layer*>::iterator m_LayerInsert;	// ָ��ǰջ��Ӧ�ò����²��λ�ã���ͨ��͵��Ӳ�ķֽ��ߣ�--������ʧЧ
		unsigned int m_LayerInsertIndex = 0;			// ָ��ǰջ��Ӧ�ò����²��λ�ã���ͨ��͵��Ӳ�ķֽ��ߣ�
	};
}

