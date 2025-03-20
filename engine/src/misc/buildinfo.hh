#ifndef TRIANGL_MISC_BUILDINFO_HH
#define TRIANGL_MISC_BUILDINFO_HH 1

#include "misc/miscdef.hh"

namespace triangl {

	enum class build_config
	{
		devel,
		prev,
		dist
	};

	enum class platform
	{
		windows,
		linux
	};

	enum class architecture
	{
		x64,
		arm64
	};

	static const char* build_config_to_string(build_config cfg)
	{
		switch (cfg)
		{
		case build_config::devel: return "devel";
		case build_config::prev:  return "prev";
		case build_config::dist:  return "dist";
		}
		return nullptr;
	}

	static const char* platform_to_string(platform platform)
	{
		switch (platform)
		{
		case platform::windows: return "windows";
		case platform::linux:   return "linux";
		}
		return nullptr;
	}

	static const char* architecture_to_string(architecture arch)
	{
		switch (arch)
		{
		case architecture::x64:   return "x64";
		case architecture::arm64: return "arm64";
		}
		return nullptr;
	}

	#ifdef TL_BUILD_DEVEL
		inline constexpr build_config gc_buildcfg = build_config::devel;
	#elif defined TL_BUILD_PREV
		inline constexpr build_config gc_buildcfg = build_config::prev;
	#elif defined TL_BUILD_DIST
		inline constexpr build_config gc_buildcfg = build_config::dist;
	#else
		#error unknown build config!
	#endif

	#ifdef TL_PLATFORM_WINDOWS
		#define TL_PLATFORM_TOKEN windows
		inline constexpr platform gc_platform = platform::windows;
	#elif defined TL_PLATFORM_LINUX
		#define TL_PLATFORM_TOKEN linux
		inline constexpr platform gc_platform = platform::linux;
	#else
		#error unknown platform!
	#endif

	#define TL_PLATFORM_NAME TL_STRINGIFY(TL_PLATFORM_TOKEN)
	#define TL_MAKE_PLATFORM_TYPE(x) TL_CONCAT(TL_PLATFORM_TOKEN, TL_CONCAT(_, x))

	// Currently only supporting x64, so no other options are possible.
	// TODO: Update once ARM64 support is added.
	// ...

	inline constexpr int gc_bitness = 64;
	inline constexpr architecture gc_arch = architecture::x64;
	// ...

}

#endif
