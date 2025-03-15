#pragma once
#include "Razel/Renderer/GraphicsContext.h"


struct  GLFWwindow;
namespace Razel {
	class OpenGLContext :public GraphicsContext
	{
	public:
		OpenGLContext(GLFWwindow* windowHandle);

		virtual void Init()override;		// ��ʼ����Ⱦ������
		virtual void SwapBuffers()override;	// ����ǰ�󻺳���
	private:
		GLFWwindow* m_WindowHandle;

	};
}