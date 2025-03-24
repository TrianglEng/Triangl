#include "TrianglPCH.h"
#include "FileUtils.h"

#include "Platform/Windows/WindowsFileUtils.h"
#include "Platform/Linux/LinuxFileUtils.h"

namespace Triangl
{
	Scope<NativeFileUtils> FileUtils::s_Instance = MakeScope<TL_MAKE_PLATFORM_TYPE(FileUtils)>();
}
