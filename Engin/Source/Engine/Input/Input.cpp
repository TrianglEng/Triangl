#include "TrianglPCH.h"
#include "Input.h"

#include "Core/Application.h"

#include "Platform/Windows/WindowsInput.h"
#include "Platform/Linux/LinuxInput.h"

namespace Triangl
{
	Scope<NativeInput> Input::s_Instance = nullptr;

	Scope<NativeInput> NativeInput::New(void* window)
	{
		return MakeScope<TL_MAKE_PLATFORM_TYPE(Input)>(window);
	}

	void Input::Init()
	{
		s_Instance = NativeInput::New(Application::Get()->GetWindow()->GetNativeWindow());
	}

	void Input::Shutdown()
	{
		s_Instance.reset();
	}
}
