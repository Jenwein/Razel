#include "rzpch.h"
#include "Platform/Windows/WindowsWindow.h"

#include "Razel/Core/Input.h"
#include "Razel/Events/KeyEvent.h"
#include "Razel/Events/MouseEvent.h"
#include "Razel/Events/ApplicationEvent.h"
#include "Razel/Renderer/Renderer.h"

#include "Platform/OpenGL/OpenGLContext.h"


namespace Razel {
	static bool s_GLFWInitialized = false;
	
	static void GLFWErrorCallback(int error_code, const char* description)
	{
		RZ_CORE_ERROR("GLFW Error ({0}): {1}", error_code, description);
	}

	WindowsWindow::WindowsWindow(const WindowProps& props)
	{
		RZ_PROFILE_FUNCTION();

		Init(props);
	}	

	WindowsWindow::~WindowsWindow()
	{
		RZ_PROFILE_FUNCTION();

		Shutdown();
	}

	void WindowsWindow::Init(const WindowProps& props)
	{
		RZ_PROFILE_FUNCTION();

		m_Data.Title = props.Title;
		m_Data.Width = props.Width;
		m_Data.Height = props.Height;

		RZ_CORE_INFO("Create window {0} ({1} , {2})", props.Title, props.Width, props.Height);
		
		// 如果GLFW未初始化
		if (!s_GLFWInitialized)
		{
			RZ_PROFILE_SCOPE("glfwInit");
			// TODO: glfwTerminate on system shutdown
			int success = glfwInit();
			RZ_CORE_ASSERT(success, "Could not intialize GLFW!");
			glfwSetErrorCallback(GLFWErrorCallback);			
			s_GLFWInitialized = true;
		}

		{
			RZ_PROFILE_SCOPE("glfwCreateWindow");

#if defined(RZ_DEBUG)
			if (Renderer::GetAPI() == RendererAPI::API::OpenGL)
				glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
#endif
			m_Window = glfwCreateWindow((int)props.Width, (int)props.Height, props.Title.c_str(), nullptr, nullptr);
			m_Context = new OpenGLContext(m_Window);
			m_Context->Init();
		}

		// 设置窗口数据指针（保存m_Data数据的指针到窗口，以便于通过窗口句柄来获取窗口相关数据）
		glfwSetWindowUserPointer(m_Window, &m_Data);
		
		// 设置垂直同步
		SetVSync(true);

		// Set GLFW callbacks
		// 注册窗口关闭回调
		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window) 
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			WindowCloseEvent event;
			data.EventCallback(event);
		});

		// 注册窗口大小变化回调
		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height) 
		{
			// 获取变化的窗口相关的数据
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			// 用当前的窗口的大小更新绑定的数据
			data.Width = width;
			data.Height = height;
			// 创建窗口变化事件
			WindowResizeEvent event(width,height);
			// 执行回调，传入事件
			data.EventCallback(event);
		});

		// 注册键盘事件回调
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
		
		// 监听文本输入
		glfwSetCharCallback(m_Window, [](GLFWwindow* window, unsigned int keycode)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			KeyTypedEvent event(static_cast<KeyCode>(keycode));
			data.EventCallback(event);
		});

		// 注册鼠标点击回调
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
		// 注册鼠标滚轮回调
		glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xOffset, double yOffset)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			MouseScrolledEvent event((float)xOffset, (float)yOffset);
			data.EventCallback(event);
		});

		// 注册鼠标位置回调
		glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xPos, double yPos)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			MouseMovedEvent event((float)xPos, (float)yPos);
			data.EventCallback(event);
		});

	}

	void WindowsWindow::Shutdown()
	{
		RZ_PROFILE_FUNCTION();

		glfwDestroyWindow(m_Window);
	}

	void WindowsWindow::OnUpdate() const
	{
		RZ_PROFILE_FUNCTION();

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
		RZ_PROFILE_FUNCTION();

		return m_Data.VSync;
	}


}