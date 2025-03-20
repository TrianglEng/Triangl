#ifndef TRIANGL_PLATFORM_LINUX_WINDOW_HH
#define TRIANGL_PLATFORM_LINUX_WINDOW_HH 1

#include "platform/desktop/desktop_window.hh"

namespace triangl {

	class linux_window : public desktop_window
	{
	public:
		linux_window(const window_props& props = {});
	};

}

#endif
