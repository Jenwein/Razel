#pragma once
#include "Razel/Events/ApplicationEvent.h"
#include "Razel/LayerStack.h"
#include "Razel/Core.h"

#include "Events/Event.h"
#include "Window.h"

#include "Razel/ImGui/ImGuiLayer.h"
#include "Razel/Renderer/Shader.h"
#include "Razel/Renderer/Buffer.h"
#include "Razel/Renderer/VertexArray.h"

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

		std::shared_ptr<Shader> m_Shader;
		std::shared_ptr<VertexArray> m_VertexArray;

		std::shared_ptr<Shader> m_BlueShader;
		std::shared_ptr<VertexArray> m_SquareVA;

		static Application* s_Instance;
	};

	// To be defined in CLIENT
	Application* CreateApplication();
}