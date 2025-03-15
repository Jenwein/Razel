#pragma once
#include "Razel/Renderer/GraphicsContext.h"


struct  GLFWwindow;
namespace Razel {
	class OpenGLContext :public GraphicsContext
	{
	public:
		OpenGLContext(GLFWwindow* windowHandle);

		virtual void Init()override;		// 初始化渲染上下文
		virtual void SwapBuffers()override;	// 交换前后缓冲区
	private:
		GLFWwindow* m_WindowHandle;

	};
}