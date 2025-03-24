#pragma once

#include "Core/Log.h"
#include "Misc/MiscDef.h"

#ifdef TL_TEST_BUILD
	#ifdef TL_PLATFORM_WINDOWS
		#define TL_DEBUGBREAK() __debugbreak()
	#elif defined TL_PLATFORM_LINUX
		#include <signal.h>
		#define TL_DEBUGBREAK() raise(SIGTRAP)
	#endif
	#define TL_ASSERT_DETAIL(logger, expr, ...) if (!(expr)) { TL_##logger##_ERROR("Assertion failed in file '" __FILE__ "' at line " TL_STRINGIFY(__LINE__) "! Expression '" #expr "' evaluated to false. " __VA_ARGS__); TL_DEBUGBREAK(); }
#else
	#define TL_DEBUGBREAK()
	#define TL_ASSERT_DETAIL(logger, expr, ...)
#endif

#define TL_CORE_ASSERT(expr, ...)   TL_ASSERT_DETAIL(CORE,   expr, __VA_ARGS__)
#define TL_EDITOR_ASSERT(expr, ...) TL_ASSERT_DETAIL(EDITOR, expr, __VA_ARGS__)
#define TL_CLIENT_ASSERT(expr, ...) TL_ASSERT_DETAIL(CLIENT, expr, __VA_ARGS__)
#define TL_ASSERT(expr, ...)        TL_CLIENT_ASSERT(expr, __VA_ARGS__)
