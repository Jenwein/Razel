#pragma once

#include <sstream>

#include "Razel/Core/Base.h"
#include "Razel/Events/Event.h"

namespace Razel
{
	// 存储窗口属性的结构体
	struct WindowProps
	{
		std::string Title;		// 窗口标题
		unsigned int Width;		// 宽度
		unsigned int Height;	// 高度

		WindowProps(const std::string& title = "Razel Engine",
					unsigned int width = 1600,
					unsigned int height = 900)
			:Title(title), Width(width), Height(height)
		{}
	};
		
	// 定义了一个跨平台的窗口接口
	class Window
	{
	public:
		using EventCallbackFn = std::function<void(Event&)>;
		virtual ~Window() = default;
		
		virtual void OnUpdate() const = 0;

		// 获取窗口宽高
		virtual unsigned int GetWidth() const = 0;
		virtual unsigned int GetHeight() const = 0;

		virtual void* GetNativeWindow() const = 0;
		
		// 设置事件回调
		virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
		
		// 控制垂直同步
		virtual void SetVSync(bool enable) = 0;
		virtual bool IsVSync() const = 0;

		// 静态工厂方法，创建Window实例（接口实现分离）
		static Scope<Window> Create(const WindowProps& props = WindowProps());

	};
}