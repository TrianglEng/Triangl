#ifndef TRIANGL_PLATFORM_WINDOWS_WINDOW_HH
#define TRIANGL_PLATFORM_WINDOWS_WINDOW_HH 1

#include "platform/desktop/desktop_window.hh"

namespace triangl {

	class windows_window : public desktop_window
	{
	public:
		windows_window(const window_props& props = {});
	};

}

#endif
