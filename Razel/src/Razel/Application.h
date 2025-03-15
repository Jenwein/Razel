#pragma once
#include "Razel/Events/ApplicationEvent.h"
#include "Razel/LayerStack.h"
#include "Razel/Core.h"
#include "Events/Event.h"
#include "Window.h"

#include "Razel/ImGui/ImGuiLayer.h"

namespace Razel {

	class RAZEL_API Application
	{
		
	public:
		Application();
		virtual ~Application();

		void Run();
		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverLayer(Layer* layer);

		inline Window& GetWindow() { return *m_Window; }

		inline static Application& Get() { return *s_Instance; }
	private:
		bool OnWindowClose(WindowCloseEvent& e);

	private:
		std::unique_ptr<Window>m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		LayerStack m_LayerStack;

		unsigned int m_VertexArray, m_VertexBuffer, m_IndexBuffer;

		static Application* s_Instance;
	};

	// To be defined in CLIENT
	Application* CreateApplication();

}