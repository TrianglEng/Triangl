#include "tlpch.hh"
#include "linux_util.hh"

namespace triangl {

    system_theme linux_platform_util::get_system_theme() const
    {
        /* TODO: add support for detection on linux */
        return system_theme::dark;
    }

}
