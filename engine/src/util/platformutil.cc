#include "tlpch.hh"
#include "platformutil.hh"

#include "platform/windows/windows_util.hh"
#include "platform/linux/linux_util.hh"

namespace triangl {

	std::unique_ptr<native_platform_util> platform_util::s_inst = std::make_unique<TL_MAKE_PLATFORM_TYPE(platform_util)>();

}
