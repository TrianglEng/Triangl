#pragma once

#include "Misc/MiscDef.h"

namespace Triangl
{
	enum class BuildConfig
	{
		Development,
		Preview,
		Shipping
	};
	
	enum class Platform
	{
		Windows,
		Linux
	};
	
	enum class Architecture
	{
		x64,
		ARM64
	};
	
	static const char* BuildConfigToString(BuildConfig config)
	{
		switch (config)
		{
		case BuildConfig::Development: return "Development";
		case BuildConfig::Preview:     return "Preview";
		case BuildConfig::Shipping:    return "Shipping";
		}
		return nullptr;
	}
	
	static const char* PlatformToString(Platform platform)
	{
		switch (platform)
		{
		case Platform::Windows: return "Windows";
		case Platform::Linux:   return "Linux";
		}
		return nullptr;
	}
	
	static const char* ArchitectureToString(Architecture arch)
	{
		switch (arch)
		{
		case Architecture::x64:   return "x64";
		case Architecture::ARM64: return "ARM64";
		}
		return nullptr;
	}
	
	#ifdef TL_DEVELOPMENT
		inline constexpr BuildConfig c_BuildCfg = BuildConfig::Development;
	#elif defined TL_PREVIEW
		inline constexpr BuildConfig c_BuildCfg = BuildConfig::Preview;
	#elif defined TL_SHIPPING
		inline constexpr BuildConfig c_BuildCfg = BuildConfig::Shipping;
	#else
		#error Unknown build configuration!
	#endif
	
	#ifdef TL_PLATFORM_WINDOWS
		#define TL_PLATFORM_TOKEN Windows
		inline constexpr Platform c_Platform = Platform::Windows;
	#elif defined TL_PLATFORM_LINUX
		#define TL_PLATFORM_TOKEN Linux
		inline constexpr Platform c_Platform = Platform::Linux;
	#else
		#error Unknown platform!
	#endif
	
	#define TL_PLATFORM_NAME TL_STRINGIFY(TL_PLATFORM_TOKEN)
	#define TL_MAKE_PLATFORM_TYPE(x) TL_CONCAT(TL_PLATFORM_TOKEN, x)
	
	// Currently only supporting x64, so no other options are possible.
	// TODO: Update once ARM64 support is added.
	// ...
	
	inline constexpr int c_Bitness = 64;
	inline constexpr Architecture c_Arch = Architecture::x64;
	// ...
}