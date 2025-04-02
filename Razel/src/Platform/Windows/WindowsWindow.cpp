#include "rzpch.h"
#include "Platform/Windows/WindowsWindow.h"

#include "Razel/Events/KeyEvent.h"
#include "Razel/Events/MouseEvent.h"
#include "Razel/Events/ApplicationEvent.h"

#include "Platform/OpenGL/OpenGLContext.h"


namespace Razel {
	static bool s_GLFWInitialized = false;
	
	static void GLFWErrorCallback(int error_code, const char* description)
	{
		RZ_CORE_ERROR("GLFW Error ({0}): {1}", error_code, description);
	}

	Scope<Window> Window::Create(const WindowProps& props)
	{
		return CreateScope<WindowsWindow>(props);
	}

	WindowsWindow::WindowsWindow(const WindowProps& props)
	{
		Init(props);
	}

	WindowsWindow::~WindowsWindow()
	{
		Shutdown();
	}

	void WindowsWindow::Init(const WindowProps& props)
	{
		m_Data.Title = props.Title;
		m_Data.Width = props.Width;
		m_Data.Height = props.Height;

		RZ_CORE_INFO("Create window {0} ({1} , {2})", props.Title, props.Width, props.Height);
		
		// ���GLFWδ��ʼ��
		if (!s_GLFWInitialized)
		{
			// TODO: glfwTerminate on system shutdown
			int success = glfwInit();
			RZ_CORE_ASSERT(success, "Could not intialize GLFW!");
			glfwSetErrorCallback(GLFWErrorCallback);			
			s_GLFWInitialized = true;
		}

		m_Window = glfwCreateWindow((int)props.Width, (int)props.Height, props.Title.c_str(), nullptr, nullptr);
		m_Context = new OpenGLContext(m_Window);
		m_Context->Init();

		// ���ô�������ָ�루����m_Data���ݵ�ָ�뵽���ڣ��Ա���ͨ�����ھ������ȡ����������ݣ�
		glfwSetWindowUserPointer(m_Window, &m_Data);
		
		// ���ô�ֱͬ��
		SetVSync(true);

		// Set GLFW callbacks
		// ע�ᴰ�ڹرջص�
		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window) 
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			WindowCloseEvent event;
			data.EventCallback(event);
		});

		// ע�ᴰ�ڴ�С�仯�ص�
		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height) 
		{
			// ��ȡ�仯�Ĵ�����ص�����
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			// �õ�ǰ�Ĵ��ڵĴ�С���°󶨵�����
			data.Width = width;
			data.Height = height;
			// �������ڱ仯�¼�
			WindowResizeEvent event(width,height);
			// ִ�лص��������¼�
			data.EventCallback(event);
		});

		// ע������¼��ص�
		glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			switch (action)
			{
				case GLFW_PRESS:
				{
					KeyPressedEvent event(key, 0);
					data.EventCallback(event);
					break;
				}
				case GLFW_RELEASE:
				{
					KeyReleasedEvent event(key);
					data.EventCallback(event);
					break;
				}
				case GLFW_REPEAT:
				{
					KeyPressedEvent event(key, 1);
					data.EventCallback(event);
					break;
				}
				default:
					break;

			}
		});
		
		// �����ı�����
		glfwSetCharCallback(m_Window, [](GLFWwindow* window, unsigned int keycode)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			KeyTypedEvent event(keycode);
			data.EventCallback(event);
		});

		// ע��������ص�
		glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			switch (action)
			{
				case GLFW_PRESS:
				{
					MouseButtonPressedEvent event(button);
					data.EventCallback(event);
					break;
				}
				case GLFW_RELEASE:
				{
					MouseButtonReleasedEvent event(button);
					data.EventCallback(event);
					break;
				}
				default:
					break;
			}

		});
		// ע�������ֻص�
		glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xOffset, double yOffset)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			MouseScrolledEvent event((float)xOffset, (float)yOffset);
			data.EventCallback(event);
		});

		// ע�����λ�ûص�
		glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xPos, double yPos)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			MouseMovedEvent event((float)xPos, (float)yPos);
			data.EventCallback(event);
		});

	}

	void WindowsWindow::Shutdown()
	{
		glfwDestroyWindow(m_Window);
	}

	void WindowsWindow::OnUpdate() const
	{
		glfwPollEvents();
		m_Context->SwapBuffers();
	}

	void WindowsWindow::SetVSync(bool enabled)
	{
		if (enabled)
			glfwSwapInterval(1);
		else
			glfwSwapInterval(0);
	}

	bool WindowsWindow::IsVSync() const
	{
		return m_Data.VSync;
	}


}