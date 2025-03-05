#pragma once

#include "Event.h"

namespace Razel {
	// 键盘事件
	class RAZEL_API KeyEvent :public Event
	{
	public:
		// 获取按键值
		inline int GetKeyCode() const { return m_KeyCode; }
		
		EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput);

	protected:
		KeyEvent(int keycode)
			:m_KeyCode(keycode){}

		int m_KeyCode;
	};

	// 按键按下事件类
	class RAZEL_API KeyPressEvent : public KeyEvent
	{
	public:
		KeyPressEvent(int keycode,int repeatCount)
			:KeyEvent(keycode),m_RepeatCount(repeatCount){}

		inline int GetRepeatCount()const { return m_RepeatCount; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyPressedEvent: " << m_KeyCode << " (" << m_RepeatCount<<" repeats)";
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyPressed);

	private:
		int m_RepeatCount;


	};

	// 按键释放事件类
	class RAZEL_API KeyReleasedEvent : public KeyEvent
	{
	public:
		KeyReleasedEvent(int keycode)
			: KeyEvent(keycode) {}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyReleasedEvent: " << m_KeyCode;
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyReleased)
	};

}