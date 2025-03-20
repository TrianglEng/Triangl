#ifndef TRIANGL_PLATFORM_DESKTOP_UTIL_HH
#define TRIANGL_PLATFORM_DESKTOP_UTIL_HH

#include "util/platformutil.hh"

namespace triangl {

	class desktop_platform_util : public native_platform_util
	{
	public:
		virtual float get_time() const override;
	};

}

#endif
