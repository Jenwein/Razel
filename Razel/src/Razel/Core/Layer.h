#pragma once
#include "Razel/Core/Base.h"
#include "Razel/Core/Timestep.h"
#include "Razel/Events/Event.h"

namespace Razel
{

	class Layer
	{
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer() = default;

		virtual void OnAttach() {}				// 层被添加到层栈时调用
		virtual void OnDetach() {}				// 层被从层栈移除时调用
		virtual void OnUpdate(Timestep ts) {}				// 每帧更新
		virtual void OnEvent(Event& event) {}	// 事件处理
		virtual void OnImGuiRender() {}			// ImGui渲染
		const std::string& GetName()const { return m_DebugName; }

	private:
		std::string m_DebugName;
	};


}