#ifndef TRIANGL_MISC_CCINFO_HH
#define TRIANGL_MISC_CCINFO_HH 1

#include <string_view>

namespace triangl {

	enum class compiler_type
	{
		unknown = 0,
		clang,
		msvc,
		gcc
	};

	struct compiler_info
	{
		std::string_view name;
		std::string_view abbreviation;
		compiler_type type;
	};

	// Clang must be checked first because it can be used with Visual Studio and even then _MSC_VER will still be defined.
	// GCC and MSVC's comparison order doesn't matteri
	#ifdef __clang__
		#define TL_COMPILER_CLANG 1
		inline constexpr compiler_info gc_ccinfo = { "Clang++", "Clang", compiler_type::clang };
	#elif defined _MSC_VER
		#define TL_COMPILER_MSVC 1
		inline constexpr compiler_info gc_ccinfo = { "Microsoft Visual C++ Compiler", "MSVC", compiler_type::msvc };
	#elif defined __GNUC__
		#define TL_COMPILER_GCC 1
		inline constexpr compiler_info gc_ccinfo = { "GNU C++ Compiler", "GCC", compiler_type::gcc };
	#else
		#define TL_COMPILER_UNKNOWN 1
		inline constexpr compiler_info gc_ccinfo = { "Unknown C++ Compiler", "???", compiler_type::unknown };
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

#endif
