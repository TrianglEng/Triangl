#pragma once

#include "Input/Input.h"

struct GLFWwindow;

namespace Triangl
{
	class DesktopInput : public NativeInput
	{
	public:
		DesktopInput(void* window);

		virtual InputState GetKeyState(KeyCode keycode) const override;
		virtual InputState GetMouseButtonState(MouseCode button) const override;
		virtual glm::vec2 GetMousePosition() const override;
	private:
		GLFWwindow* m_Window = nullptr;
	};
}
