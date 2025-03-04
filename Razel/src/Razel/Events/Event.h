#pragma once

#include "Razel/Core.h"

#include <string>
#include <functional>

namespace Razel
{
	// Events in Hazel are currently blocking, meaning when an event occurs it
	// immediately gets dispatched and must be dealt with right then an there.
	// For the future, a better strategy might be to buffer events in an event
	// bus and process them during the "event" part of the update stage.

	// 事件类型
	enum class EventType
	{
		None = 0,
		WindowClose,WindowResize,WindowFocus,WindowLostFocus,WindowMoved,	// 窗口事件
		AppTick,AppUpdate,AppRender,										// 应用事件
		KeyPressed,KeyReleased,												// 键盘事件
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
// GetStaticType 静态获取类型
// GetEventType 获取事件类型
// GetName 获取类型名称
#define EVENT_CLASS_TYPE(type) static EventType GetStaticType(){return EventType::##type;}\
							   virtual EventType GetEventType()const override{return GetStaticType();}\
							   virtual const char* GetName() const override {return #type;}

#define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags()const override {return category;}

	// 作为所有事件的基类
	class RAZEL_API Event 
	{
		//friend class EventDispatcher;
	public:
		
		virtual EventType GetEventType() const = 0;					// 获取事件类型
		virtual const char* GetName() const = 0;					// 获取事件名称
		virtual int GetCategoryFlags() const = 0;					// 获取事件类别标签
		virtual std::string ToString() const { return GetName(); }	// 将事件信息转换为字符

		// 检查事件是否属于特定类别（IsHasCategory？）
		inline bool IsInCategory(EventCategory category) const
		{
			return GetCategoryFlags() & category;
		}

	private:
		bool m_Handled = false;		// 事件是否被处理
	};


	// 事件分发器
	class EventDispatcher
	{
		template<typename T>
		using EventFn = std::function<bool(T&)>;
	public:
		EventDispatcher(Event& event)
			:m_Event(event){}

		// 分发事件
		template<typename T>
		bool Dispatch(EventFn<T> func)
		{
			if (m_Event.GetEventType() == T::GetStaticType())
			{
				//--
				m_Event.m_Handled = func(*(T*)&m_Event);
				return true;
			}
			return false;
		}

	private:
		Event& m_Event;
	};
	inline std::ostream& operator<<(std::ostream os, const Event& e)
	{
		return os << e.ToString();
	}

}