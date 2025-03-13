#pragma once

#include "Razel/Core.h"
#include "Razel/Events/Event.h"

namespace Razel
{

	class RAZEL_API Layer
	{
	public: 
		Layer(const std::string& name = "Layer");
		virtual ~Layer();

		virtual void OnAttach() {}				// �㱻��ӵ���ջʱ����
		virtual void OnDetach() {}				// �㱻�Ӳ�ջ�Ƴ�ʱ����
		virtual void OnUpdate() {}				// ÿ֡����
		virtual void OnEvent(Event& event) {}	// �¼�����
		virtual void OnImGuiRender(){}			// ImGui��Ⱦ
		inline const std::string& GetName()const { return m_DebugName; }

	private:
		std::string m_DebugName;
	};


}