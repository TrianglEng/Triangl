#pragma once

#include "Core/Base.h"

#include "Input/KeyCodes.h"
#include "Input/MouseCodes.h"

namespace Triangl
{
	enum class InputState
	{
		Pressed   = 1,
		Repeating = 2,
		Released  = 0
	};

	class NativeInput
	{
	public:
		virtual ~NativeInput() = default;
	
		virtual InputState GetKeyState(KeyCode keycode) const = 0;
		virtual InputState GetMouseButtonState(MouseCode button) const = 0;
		virtual glm::vec2 GetMousePosition() const = 0;

		static Scope<NativeInput> New(void* window);
	};

	class Input
	{
	public:
		static void Init();
		static void Shutdown();

		static InputState GetKeyState(KeyCode keycode)
		{
			return s_Instance->GetKeyState(keycode);
		}

		static bool IsKeyPressed(KeyCode keycode)
		{
			return GetKeyState(keycode) == InputState::Pressed;
		}

		static bool IsKeyRepeating(KeyCode keycode)
		{
			return GetKeyState(keycode) == InputState::Repeating;
		}

		static bool IsKeyDown(KeyCode keycode)
		{
			InputState state = GetKeyState(keycode);
			return state == InputState::Pressed || state == InputState::Repeating;
		}

		static bool IsKeyReleased(KeyCode keycode)
		{
			return GetKeyState(keycode) == InputState::Released;
		}

		static InputState GetMouseButtonState(MouseCode button)
		{
			return s_Instance->GetMouseButtonState(button);
		}

		static bool IsMouseButtonPressed(MouseCode button)
		{
			return GetMouseButtonState(button) == InputState::Pressed;
		}

		static bool IsMouseButtonReleased(MouseCode button)
		{
			return GetMouseButtonState(button) == InputState::Released;
		}

		static glm::vec2 GetMousePosition()
		{
			return s_Instance->GetMousePosition();
		}

		static float GetMouseX()
		{
			return GetMousePosition().x;
		}

		static float GetMouseY()
		{
			return GetMousePosition().y;
		}
	private:
		static Scope<NativeInput> s_Instance;
	};
}
