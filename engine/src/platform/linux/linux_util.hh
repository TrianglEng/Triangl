#ifndef TRIANGL_PLATFORM_LINUX_UTIL_HH
#define TRIANGL_PLATFORM_LINUX_UTIL_HH 1

#include "platform/desktop/desktop_util.hh"

namespace triangl {

	class linux_platform_util : public desktop_platform_util
	{
	public:
		virtual system_theme get_system_theme() const override;
	};

}

#endif
