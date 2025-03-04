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

	// �¼�����
	enum class EventType
	{
		None = 0,
		WindowClose,WindowResize,WindowFocus,WindowLostFocus,WindowMoved,
		AppTick,AppUpdate,AppRender,
		KeyPressed,KeyReleased,
		MouseButtonPressed,MouseButtonReleased,MouseMoved,MouseScrolled

	};

	// �¼����
	enum EventCategory
	{
		None = 0,
		EventCategoryApplication = BIT(0),	//
		EventCategoryInput = BIT(1),		//�����¼�
		EventCategoryKeyboard = BIT(2),		//�����¼�
		EventCategoryMouse = BIT(3),		//����¼�
		EventCategoryMouseButton = BIT(4)	//������¼�
	};

//## ��Ԥ�������� token ���ӷ�,�� type ƴ�ӳ� EventType::KeyPressed ������ö��ֵ��
#define EVENT_CLASS_TYPE(type) static EventType GetStaticType(){return EventType::##type;}\
																virtual EventType GetEventType()const override{return GetStaticType();}\
																virtual const char* GetName() const override {return #type;}		

#define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags()const override {return category;}

	// ��Ϊ�����¼��Ļ���
	class RAZEL_API Event 
	{
		




	};


}