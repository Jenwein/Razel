#pragma once

#include "Razel/Core/Base.h"

#include "Razel/Core/Window.h"
#include "Razel/Core/LayerStack.h"
#include "Razel/Events/Event.h"
#include "Razel/Events/ApplicationEvent.h"

#include "Razel/Core/Timestep.h"

#include "Razel/ImGui/ImGuiLayer.h"

int main(int argc, char** argv);

namespace Razel {

	class RAZEL_API Application
	{
	public:
		Application(const std::string& name = "Razel App");
		virtual ~Application();

		void Close();

		ImGuiLayer* GetImGuiLayer() { return m_ImGuiLayer; }

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverLayer(Layer* layer);

		Window& GetWindow() { return *m_Window; }
		static Application& Get() { return *s_Instance; }
	private:
		void Run();
		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);
	private:
		std::unique_ptr<Window>m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		bool m_Minimized = false;

		LayerStack m_LayerStack;
		float m_LastFrameTime = 0.0f;
		
	private:
		static Application* s_Instance;
		friend int ::main(int argc, char** argv);	
	};

	// To be defined in CLIENT
	Application* CreateApplication();
}