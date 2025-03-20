#include "tlpch.hh"
#include "window.hh"

#include "platform/windows/windows_window.hh"
#include "platform/linux/linux_window.hh"

namespace triangl {

	std::unique_ptr<window> window::create(const window_props& props)
	{
		return std::make_unique<TL_MAKE_PLATFORM_TYPE(window)>(props);
	}

}
