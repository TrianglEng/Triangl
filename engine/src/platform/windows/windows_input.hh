#ifndef TRIANGL_PLATFORM_WINDOWS_INPUT_HH
#define TRIANGL_PLATFORM_WINDOWS_INPUT_HH 1

#include "platform/desktop/desktop_input.hh"

namespace triangl {

	class windows_input : public desktop_input
	{
	public:
		windows_input(void* native_window_handle);
	};

}

#endif
