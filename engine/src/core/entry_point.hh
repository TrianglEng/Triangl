#ifndef TRIANGL_CORE_ENTRY_POINT_HH
#define TRIANGL_CORE_ENTRY_POINT_HH 1

#include "core/application.hh"

namespace triangl {

	int engine_main(int argc, char** argv)
	{
		application* app = create_application_instance({ argv, argc });
		app->run();

		delete app;
		return 0;
	}

}

#if defined TL_BUILD_DIST && defined TL_PLATFORM_WINDOWS

#include <Windows.h>

int CALLBACK WinMain
(
	_In_     HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_     LPSTR     lpCmdLine,
	_In_     int       nCmdShow
)
{
	return triangl::engine_main(__argc, __argv);
}

#else

int main(int argc, char** argv)
{
	return triangl::engine_main(argc, argv);
}

#endif

#endif
