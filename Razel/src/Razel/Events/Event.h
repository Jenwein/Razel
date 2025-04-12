#pragma once
#include "rzpch.h"

#include "Razel/Core/Base.h"

namespace Razel
{
	// Events in Hazel are currently blocking, meaning when an event occurs it 
	// immediately gets dispatched and must be dealt with right then an there. 
	// For the future, a better strategy might be to buffer events in an event
	// bus and process them during the "event" part of the update stage.
	// 事件目前是阻塞的，意味着当事件发生时，立即被分发且必须立即被处理，
	// 更好的策略可能是在事件总线中缓冲事件，并在更新阶段的“事件”部分处理它们 
	
	// 事件类型
	enum class EventType
	{
		None = 0,
		WindowClose,WindowResize,WindowFocus,WindowLostFocus,WindowMoved,	// 窗口事件
		AppTick,AppUpdate,AppRender,										// 应用事件
		KeyPressed,KeyReleased, KeyTyped,									// 键盘事件
		MouseButtonPressed,MouseButtonReleased,MouseMoved,MouseScrolled		// 鼠标事件

	};

	// 事件类别
	enum EventCategory
	{
		None = 0,
		EventCategoryApplication	= BIT(0),	//应用程序事件
		EventCategoryInput			= BIT(1),	//输入事件
		EventCategoryKeyboard		= BIT(2),	//键盘事件
		EventCategoryMouse			= BIT(3),	//鼠标事件
		EventCategoryMouseButton	= BIT(4)	//鼠标点击事件
	};

// '#'-字符串化操作,'##'-预处理拼接字符
// GetStaticType 返回事件类型
// GetEventType 返回具体实例的类型
// GetName 获取类型名称
#define EVENT_CLASS_TYPE(type) static EventType GetStaticType(){return EventType::##type;}\
							   virtual EventType GetEventType()const override{return GetStaticType();}\
							   virtual const char* GetName() const override {return #type;}

#define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags()const override {return category;}

	// 作为所有事件的基类
	class Event 
	{
	public:
		bool Handled = false;		// 事件是否被处理

		virtual EventType GetEventType() const = 0;					// 获取事件类型
		virtual const char* GetName() const = 0;					// 获取事件名称(用于调试)
		virtual int GetCategoryFlags() const = 0;					// 获取事件类别标签
		virtual std::string ToString() const { return GetName(); }	// 返回事件类型的字符串表示(用于调试)

		// 检查事件是否属于特定类别（IsHasCategory？）
		bool IsInCategory(EventCategory category) const
		{
			return GetCategoryFlags() & category;
		}


	};


	// 事件分发器
	class EventDispatcher
	{
	public:
		EventDispatcher(Event& event)
			:m_Event(event) 
		{
		}

		// F will be deduced by the compiler
		template<typename T, typename F>
		bool Dispatch(const F& func)
		{
			if (m_Event.GetEventType() == T::GetStaticType())
			{
				m_Event.Handled = func(static_cast<T&>(m_Event));
				return true;
			}
			return false;
		}

	private:
		Event& m_Event;
	};

	//inline std::ostream& operator<<(std::ostream& os, const Event& e)
	//{
	//	return os << e.ToString();
	//}
	//当前版本的spdlog支持下面的方法以用来格式化
	inline std::string format_as(const Event& e) {
		return e.ToString();
	}

}