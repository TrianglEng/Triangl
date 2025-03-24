#pragma once

#include <string_view>

namespace Triangl
{
	enum class Compilers
	{
		Unknown = 0,
		Clang,
		MSVC,
		GCC
	};

	struct CompilerInfo
	{
		std::string_view Name;
		std::string_view Abbreviation;
		Compilers Compiler = Compilers::Unknown;
	};

	// Clang must be checked first because it can be used with Visual Studio and even then _MSC_VER will still be defined.
	// GCC and MSVC's comparison order doesn't matteri
	#ifdef __clang__
		#define TL_COMPILER_CLANG 1
		inline constexpr CompilerInfo c_CompilerInfo = { "Clang++", "Clang", Compilers::Clang };
	#elif defined _MSC_VER
		#define TL_COMPILER_MSVC 1
		inline constexpr CompilerInfo c_CompilerInfo = { "Microsoft Visual C++ Compiler", "MSVC", Compilers::MSVC };
	#elif defined __GNUC__
		#define TL_COMPILER_GCC 1
		inline constexpr CompilerInfo c_CompilerInfo = { "GNU C++ Compiler", "GCC", Compilers::GCC };
	#else
		#define TL_COMPILER_UNKNOWN 1
		inline constexpr CompilerInfo c_CompilerInfo = { "Unknown C++ Compiler", "???", Compilers::Unknown };
		#warning unknown and not officially supported compiler is getting used
	#endif

	// MSVC doesn't set __cplusplus correctly without a specific compilation flag, and we cannot know if the flag is set.
	// However, _MSVC_LANG is always defined correctly so for MSVC we'll use that.
	#ifdef TL_COMPILER_MSVC
		#define TL_CPLUSPLUS_STANDARD _MSVC_LANG
	#else
		#define TL_CPLUSPLUS_STANDARD __cplusplus
	#endif
}
