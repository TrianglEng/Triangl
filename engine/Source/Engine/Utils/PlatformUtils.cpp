#include "TrianglPCH.h"
#include "PlatformUtils.h"

#include "Platform/Windows/WindowsPlatformUtils.h"
#include "Platform/Linux/LinuxPlatformUtils.h"

namespace Triangl
{
	Scope<NativePlatformUtils> PlatformUtils::s_Instance = MakeScope<TL_MAKE_PLATFORM_TYPE(PlatformUtils)>();
}
