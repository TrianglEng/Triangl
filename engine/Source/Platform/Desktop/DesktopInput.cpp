#include "TrianglPCH.h"
#include "DesktopInput.h"

#include <GLFW/glfw3.h>

namespace Triangl
{
	DesktopInput::DesktopInput(void* window)
		: m_Window((GLFWwindow*) window)
	{
		TL_CORE_ASSERT(window, "Input object's window handle is null!");
	}

	InputState DesktopInput::GetKeyState(KeyCode keycode) const
	{
		return (InputState) glfwGetKey(m_Window, (KeyCode) keycode);
	}

	InputState DesktopInput::GetMouseButtonState(MouseCode button) const
	{
		return (InputState) glfwGetMouseButton(m_Window, (MouseCode) button);
	}

	glm::vec2 DesktopInput::GetMousePosition() const
	{
		double x, y;
		glfwGetCursorPos(m_Window, &x, &y);
		return { (float) x, (float) y };
	}
}
