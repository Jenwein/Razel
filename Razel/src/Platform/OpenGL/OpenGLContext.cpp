#include "rzpch.h"
#include "Platform/OpenGL/OpenGLContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace Razel
{
	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
		:m_WindowHandle(windowHandle)
	{
		RZ_CORE_ASSERT(windowHandle, "Window handle is null!");
	
	}

	void OpenGLContext::Init()
	{
		RZ_PROFILE_FUNCTION();

		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		RZ_CORE_ASSERT(status, "Failed to initialize Glad!");
		RZ_CORE_INFO("OpenGL Info:");
		RZ_CORE_INFO("  Vendor: {0}",(const char*)glGetString(GL_VENDOR));
		RZ_CORE_INFO("  Renderer: {0}",(const char*)glGetString(GL_RENDERER));
		RZ_CORE_INFO("  Version: {0}",(const char*)glGetString(GL_VERSION));
	}

	void OpenGLContext::SwapBuffers()
	{
		RZ_PROFILE_FUNCTION();

		glfwSwapBuffers(m_WindowHandle);
	}

}