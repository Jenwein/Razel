#pragma once

#include "rzpch.h"

#include "Razel/Core.h"
#include "Razel/Events/Event.h"

namespace Razel
{
	// �洢�������ԵĽṹ��
	struct WindowProps
	{
		std::string Title;		// ���ڱ���
		unsigned int Width;		// ���
		unsigned int Height;	// �߶�

		WindowProps(const std::string& title = "Razel Engine",
					unsigned int width = 1280,
					unsigned int height = 720)
			:Title(title), Width(width), Height(height)
		{}
	};
		
	// ������һ����ƽ̨�Ĵ��ڽӿ�
	class RAZEL_API Window
	{
	public:
		using EventCallbackFn = std::function<void(Event&)>;
		virtual ~Window() {}
		
		virtual void OnUpdate() const = 0;

		// ��ȡ���ڿ��
		virtual unsigned int GetWidth() const = 0;
		virtual unsigned int GetHeight() const = 0;

		// �����¼��ص�
		virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
		
		// ���ƴ�ֱͬ��
		virtual void SetVSync(bool enable) = 0;
		virtual bool IsVSync() const = 0;

		// ��̬��������������Windowʵ�����ӿ�ʵ�ַ��룩
		static Window* Create(const WindowProps& props = WindowProps());

	};
}