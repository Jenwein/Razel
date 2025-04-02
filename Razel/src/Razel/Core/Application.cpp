#include "rzpch.h"

#include "Razel/Core/Application.h"

#include "Razel/Core/Log.h"

#include "Razel/Renderer/Renderer.h"

#include "Razel/Core/Input.h"

#include <GLFW/glfw3.h>
namespace Razel {
	
	Application* Application::s_Instance = nullptr;
	
	Application::Application()
	{
		RZ_PROFILE_FUNCTION();

		RZ_CORE_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;

		m_Window = Window::Create();
		m_Window->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));

		Renderer::Init();

		m_ImGuiLayer = new ImGuiLayer();
		PushOverLayer(m_ImGuiLayer);
	}

	Application::~Application()
	{
		RZ_PROFILE_FUNCTION();
		Renderer::Shutdown();
	}

	void Application::OnEvent(Event& e)
	{
		RZ_PROFILE_FUNCTION();

		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(Application::OnWindowClose));
		dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENT_FN(Application::OnWindowResize));
		//RZ_CORE_TRACE("{0}", e);

		// 事件处理自顶向下遍历
		for (auto it = m_LayerStack.end();it !=m_LayerStack.begin();)
		{
			(*--it)->OnEvent(e);
			// 如果事件被当前层处理则停止继续传递
			if (e.Handled)
			{
				break;
			}
		}
	}

	void Application::PushLayer(Layer* layer)
	{
		RZ_PROFILE_FUNCTION();

		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverLayer(Layer* overlayer)
	{
		RZ_PROFILE_FUNCTION();

		m_LayerStack.PushOverLayer(overlayer);
		overlayer->OnAttach();
	}
	void Application::Run()
	{
		RZ_PROFILE_FUNCTION();

		while (m_Running)
		{
			RZ_PROFILE_SCOPE("RunLoop")
			float time = (float)glfwGetTime();
			Timestep timestep = time - m_LastFrameTime;

			m_LastFrameTime = time;

			if (!m_Minimized)
			{
				{
					RZ_PROFILE_SCOPE("LayerStack OnUpdate");
					for (Layer* layer : m_LayerStack)
						layer->OnUpdate(timestep);
				}

				m_ImGuiLayer->Begin();
				{
					RZ_PROFILE_SCOPE("LayerStack OnImGuiRender");
					
					for (Layer* layer : m_LayerStack)
						layer->OnImGuiRender();
					
				}
				m_ImGuiLayer->End();
			}	
			m_Window->OnUpdate();
		}
	}
	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		RZ_PROFILE_FUNCTION();

		m_Running = false;
		return true;
	}

	bool Application::OnWindowResize(WindowResizeEvent& e)
	{
		RZ_PROFILE_FUNCTION();

		if (e.GetWidth() == 0 || e.GetHeight() == 0)
		{
			m_Minimized = true;
			return false;
		}

		m_Minimized = false;
		Renderer::OnWindowResize(e.GetWidth(), e.GetHeight());

		return false;
	}


}