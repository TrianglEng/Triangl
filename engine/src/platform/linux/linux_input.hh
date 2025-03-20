#ifndef TRIANGL_PLATFORM_LINUX_INPUT_HH
#define TRIANGL_PLATFORM_LINUX_INPUT_HH 1

#include "platform/desktop/desktop_input.hh"

namespace triangl {

	class linux_input : public desktop_input
	{
	public:
		linux_input(void* native_window_handle);
	};

}

#endif
