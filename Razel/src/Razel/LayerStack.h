#pragma once

#include "Razel/Core.h"
#include "Layer.h"

namespace Razel
{
	class RAZEL_API LayerStack
	{
		// |--------------------��ջ--------------------------|
		// | ��ͨ��ջ (Layer Stack) | ���Ӳ�ջ (Overlay Stack) |
	public:
		LayerStack();
		~LayerStack();

		void PushLayer(Layer* layer);			// �����ͨ��
		void PushOverLayer(Layer* overlayer);	// ��ӵ��Ӳ�
		void PopLayer(Layer* layer);			// �Ƴ���ͨ��
		void PopOverLayer(Layer* overlayer);	// �Ƴ����Ӳ�

		std::vector<Layer*>::iterator begin() { return m_Layers.begin(); }
		std::vector<Layer*>::iterator end() { return m_Layers.end(); }

	private:
		std::vector<Layer*> m_Layers;					// �洢��ջ�����в�ָ��
		//std::vector<Layer*>::iterator m_LayerInsert;	// ָ��ǰջ��Ӧ�ò����²��λ�ã���ͨ��͵��Ӳ�ķֽ��ߣ�--������ʧЧ
		unsigned int m_LayerInsertIndex = 0;			// ָ��ǰջ��Ӧ�ò����²��λ�ã���ͨ��͵��Ӳ�ķֽ��ߣ�
	};
}

