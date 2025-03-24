#include "TrianglPCH.h"
#include "LinuxPlatformUtils.h"

namespace Triangl
{
    SystemTheme LinuxPlatformUtils::GetSystemTheme() const
    {
        /* TODO: add support for detection on linux */
        return SystemTheme::Dark;
    }
}
