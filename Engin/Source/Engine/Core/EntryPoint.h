#pragma once

#include "Core/Application.h"

namespace Triangl
{
	int EngineMain(int argc, char** argv)
	{
		Application* application = CreateApplication({ argv, argc });
		application->Run();

		delete application;
		return 0;
	}
}

#if defined TL_SHIPPING && defined TL_PLATFORM_WINDOWS

#include <Windows.h>

int CALLBACK WinMain
(
	_In_     HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_     LPSTR     lpCmdLine,
	_In_     int       nCmdShow
)
{
	return Triangl::EngineMain(__argc, __argv);
}

#else

int main(int argc, char** argv)
{
	return Triangl::EngineMain(argc, argv);
}

#endif
