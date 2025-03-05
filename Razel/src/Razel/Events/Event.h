#pragma once
#include "rzpch.h"

#include "Razel/Core.h"


namespace Razel
{
	// Events in Hazel are currently blocking, meaning when an event occurs it 
	// immediately gets dispatched and must be dealt with right then an there. 
	// For the future, a better strategy might be to buffer events in an event
	// bus and process them during the "event" part of the update stage.
	// �¼�Ŀǰ�������ģ���ζ�ŵ��¼�����ʱ���������ַ��ұ�������������
	// ���õĲ��Կ��������¼������л����¼������ڸ��½׶εġ��¼������ִ������� 
	
	// �¼�����
	enum class EventType
	{
		None = 0,
		WindowClose,WindowResize,WindowFocus,WindowLostFocus,WindowMoved,	// �����¼�
		AppTick,AppUpdate,AppRender,										// Ӧ���¼�
		KeyPressed,KeyReleased,												// �����¼�
		MouseButtonPressed,MouseButtonReleased,MouseMoved,MouseScrolled		// ����¼�

	};

	// �¼����
	enum EventCategory
	{
		None = 0,
		EventCategoryApplication	= BIT(0),	//Ӧ�ó����¼�
		EventCategoryInput			= BIT(1),	//�����¼�
		EventCategoryKeyboard		= BIT(2),	//�����¼�
		EventCategoryMouse			= BIT(3),	//����¼�
		EventCategoryMouseButton	= BIT(4)	//������¼�
	};

// '#'-�ַ���������,'##'-Ԥ����ƴ���ַ�
// GetStaticType �����¼�����
// GetEventType ���ؾ���ʵ��������
// GetName ��ȡ��������
#define EVENT_CLASS_TYPE(type) static EventType GetStaticType(){return EventType::##type;}\
							   virtual EventType GetEventType()const override{return GetStaticType();}\
							   virtual const char* GetName() const override {return #type;}

#define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags()const override {return category;}

	// ��Ϊ�����¼��Ļ���
	class RAZEL_API Event 
	{
		//friend class EventDispatcher;
	public:
		
		virtual EventType GetEventType() const = 0;					// ��ȡ�¼�����
		virtual const char* GetName() const = 0;					// ��ȡ�¼�����(���ڵ���)
		virtual int GetCategoryFlags() const = 0;					// ��ȡ�¼�����ǩ
		virtual std::string ToString() const { return GetName(); }	// �����¼����͵��ַ�����ʾ(���ڵ���)

		// ����¼��Ƿ������ض����IsHasCategory����
		inline bool IsInCategory(EventCategory category) const
		{
			return GetCategoryFlags() & category;
		}

	private:
		bool m_Handled = false;		// �¼��Ƿ񱻴���
	};


	// �¼��ַ���
	class EventDispatcher
	{
		template<typename T>
		using EventFn = std::function<bool(T&)>;
	public:
		EventDispatcher(Event& event)
			:m_Event(event){}

		// �ַ��¼�
		template<typename T>
		bool Dispatch(EventFn<T> func)
		{
			if (m_Event.GetEventType() == T::GetStaticType())
			{
				// ǿ������ת��
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