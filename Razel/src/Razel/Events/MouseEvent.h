#pragma once

#include "Event.h"
#include "Razel/Core/MouseCodes.h"
namespace Razel {

	// 鼠标移动事件类
	class MouseMovedEvent:public Event
	{
	public:
		MouseMovedEvent(const float x,const float y)
			:m_MouseX(x),m_MouseY(y)
		{}

		float GetX()const { return m_MouseX; }
		float GetY()const { return m_MouseY; }

		std::string ToString() const override 
		{
			std::stringstream ss;
			ss << "MouseMovedEvent: " << m_MouseX << ", " << m_MouseY;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseMoved);
		EVENT_CLASS_CATEGORY(EventCategoryMouse|EventCategoryInput);
	private:
		float m_MouseX,m_MouseY;
	};

	// 鼠标滚轮事件类
	class MouseScrolledEvent :public Event
	{
	public:
		MouseScrolledEvent(const float xOffset, const float yOffset)
			:m_XOffset(xOffset), m_YOffset(yOffset)
		{}

		float GetXOffset()const { return m_XOffset; }
		float GetYOffset()const { return m_YOffset; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseScrolledEvent: " << m_XOffset << ", " << m_YOffset;
			return ss.str();
		}
		EVENT_CLASS_TYPE(MouseScrolled);
		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput);
	private:
		float m_XOffset, m_YOffset;
	};

	// 鼠标按键事件类
	class MouseButtonEvent :public Event
	{
	public:
		MouseCode GetMouseButton()const { return m_Button; }

		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput | EventCategoryMouseButton);


	protected:
		MouseButtonEvent(const MouseCode button)
			:m_Button(button){}

		MouseCode m_Button;
	};

	//鼠标按键按下事件类
	class MouseButtonPressedEvent :public MouseButtonEvent
	{
	public:
		MouseButtonPressedEvent(const MouseCode button)
			:MouseButtonEvent(button){}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonPressedEvent: " << m_Button;
			return ss.str();
		}
		
		EVENT_CLASS_TYPE(MouseButtonPressed);
	};

	// 鼠标按键释放事件类
	class MouseButtonReleasedEvent :public MouseButtonEvent
	{
	public:
		MouseButtonReleasedEvent(const MouseCode button)
			:MouseButtonEvent(button) {}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonReleasedEvent: " << m_Button;
			return ss.str();
		}
		EVENT_CLASS_TYPE(MouseButtonReleased);
	};


}
