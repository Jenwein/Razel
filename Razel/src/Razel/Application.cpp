#include "rzpch.h"

#include "Application.h"

#include "Razel/Log.h"

#include "glad/glad.h"

#include "Input.h"
namespace Razel {
	
	Application* Application::s_Instance = nullptr;
	
	Application::Application()
	{
		RZ_CORE_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;

		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));

		unsigned int id;
		glGenVertexArrays(1, &id);

	}

	Application::~Application()
	{

	}
	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(Application::OnWindowClose));
	
		RZ_CORE_TRACE("{0}", e);

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
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverLayer(Layer* overlayer)
	{
		m_LayerStack.PushOverLayer(overlayer);
		overlayer->OnAttach();
	}

	void Application::Run()
	{

		while (m_Running)
		{
			glClearColor(1, 0, 1, 1);
			glClear(GL_COLOR_BUFFER_BIT);
			for (Layer* layer : m_LayerStack)
				layer->OnUpdate();

			m_Window->OnUpdate();
		}
	}
	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = 0;
		return true;
	}


}