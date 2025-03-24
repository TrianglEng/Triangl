#pragma once

#include "Core/Assert.h"

#include "Misc/BuildInfo.h"
#include "Misc/MiscDef.h"
#include "Misc/CompilerInfo.h"

#ifdef TL_PLATFORM_WINDOWS
	typedef SSIZE_T ssize_t;
#elif defined TL_PLATFORM_LINUX
	#include <sys/types.h>
#endif
