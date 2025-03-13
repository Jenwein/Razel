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

		virtual void OnAttach() {}				// 层被添加到层栈时调用
		virtual void OnDetach() {}				// 层被从层栈移除时调用
		virtual void OnUpdate() {}				// 每帧更新
		virtual void OnEvent(Event& event) {}	// 事件处理
		virtual void OnImGuiRender(){}			// ImGui渲染
		inline const std::string& GetName()const { return m_DebugName; }

	private:
		std::string m_DebugName;
	};


}