#pragma once
#include "Razel/Core/Layer.h"

#include "Razel/Events/ApplicationEvent.h"
#include "Razel/Events/MouseEvent.h"
#include "Razel/Events/KeyEvent.h"
namespace Razel
{
	class ImGuiLayer :public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer() = default;
	
		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnEvent(Event& e) override;
		virtual void OnImGuiRender() override;
		

		void Begin();
		void End();
		void BlockEvents(bool block) { m_BlockEvents = block; }
		bool GetBlockEvents() const { return m_BlockEvents; }
	private:
		void SetDarkThemeColors();

	private:
		float m_Time = 0.0f;
		bool m_BlockEvents = true;
	};

}
