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
		WindowClose,WindowResize,WindowFocus,WindowLostFocus,WindowMoved,
		AppTick,AppUpdate,AppRender,
		KeyPressed,KeyReleased,
		MouseButtonPressed,MouseButtonReleased,MouseMoved,MouseScrolled

	};

	// 事件类别
	enum EventCategory
	{
		None = 0,
		EventCategoryApplication = BIT(0),	//
		EventCategoryInput = BIT(1),		//输入事件
		EventCategoryKeyboard = BIT(2),		//键盘事件
		EventCategoryMouse = BIT(3),		//鼠标事件
		EventCategoryMouseButton = BIT(4)	//鼠标点击事件
	};

//## 是预处理器的 token 连接符,把 type 拼接成 EventType::KeyPressed 这样的枚举值。
#define EVENT_CLASS_TYPE(type) static EventType GetStaticType(){return EventType::##type;}\
																virtual EventType GetEventType()const override{return GetStaticType();}\
																virtual const char* GetName() const override {return #type;}		

#define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags()const override {return category;}

	// 作为所有事件的基类
	class RAZEL_API Event 
	{
		




	};


}