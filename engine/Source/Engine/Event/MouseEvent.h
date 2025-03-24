#pragma once

#include "Event/Event.h"
#include "Input/MouseCodes.h"

#include <sstream>

namespace Triangl
{
	class MouseEvent : public Event
	{
	public:
		EVENT_CATEGORY_DETAIL(EC_Input | EC_Mouse);
	};

	class MouseMovedEvent : public MouseEvent
	{
	public:
		MouseMovedEvent(float xPos, float yPos)
			: m_PosX(xPos), m_PosY(yPos) {}

		virtual std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseMovedEvent: " << m_PosX << ", " << m_PosY;
			return ss.str();
		}

		float GetPosX() const { return m_PosY; }
		float GetPosY() const { return m_PosY; }

		EVENT_TYPE_DETAIL(MouseMoved);
	private:
		float m_PosX = 0.0f, m_PosY = 0.0f;
	};

	class MouseScrolledEvent : public MouseEvent
	{
	public:
		MouseScrolledEvent(float xOff, float yOff)
			: m_OffsetX(xOff), m_OffsetY(yOff) {}

		virtual std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseScrolledEvent: " << m_OffsetX << ", " << m_OffsetY;
			return ss.str();
		}

		float GetOffsetX() const { return m_OffsetX; }
		float GetOffsetY() const { return m_OffsetY; }

		EVENT_TYPE_DETAIL(MouseScrolled);
	private:
		float m_OffsetX = 0.0f, m_OffsetY = 0.0f;
	};

	class MouseButtonEvent : public MouseEvent
	{
	public:
		virtual std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonEvent: " << m_Button;
			return ss.str();
		}

		MouseCode GetButton() const { return m_Button; }
		EVENT_CATEGORY_DETAIL(EC_Input | EC_Mouse | EC_Mouse_Button);
	protected:
		MouseButtonEvent(MouseCode button)
			: m_Button(button) {}

		MouseCode m_Button = (MouseCode) 0;
	};

	class MouseButtonPressedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonPressedEvent(MouseCode button)
			: MouseButtonEvent(button) {}

		virtual std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonPressedEvent: " << m_Button;
			return ss.str();
		}

		EVENT_TYPE_DETAIL(MouseButtonPressed);
	};
	
	class MouseButtonReleasedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonReleasedEvent(MouseCode button)
			: MouseButtonEvent(button) {}

		virtual std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonReleasedEvent: " << m_Button;
			return ss.str();
		}

		EVENT_TYPE_DETAIL(MouseButtonReleased);
	};
}
