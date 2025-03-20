project "triangl"
	language "c++"
	cppdialect "c++17"
	kind "staticlib"
	
	targetdir "%{outdir.bin}/%{prj.name}"
	objdir    "%{outdir.obj}/%{prj.name}"
	
	pchheader "tlpch.hh"
	pchsource "src/tlpch.cc"

	files
	{
		"src/**.hh",
		"src/**.cc"
	}
	
	includedirs
	{
		"src",
		
		"%{incdir.fmt}",
		"%{incdir.spdlog}",
		"%{incdir.glm}",
		"%{incdir.glfw}",
		"%{incdir.glad}"
	}
	
	links
	{
		"glfw",
		"glad"
	}
	
	filter "system:windows"
		systemversion "latest"
		defines
		{
			"TL_PLATFORM_WINDOWS",

			"_CRT_SECURE_NO_WARNINGS",
			"_SILENCE_ALL_MS_EXT_DEPRECATION_WARNINGS"
		}
		excludes
		{
			"src/platform/linux/**.cc"
		}

	filter "system:linux"
		defines
		{
			"TL_PLATFORM_LINUX"
		}
		excludes
		{
			"src/platform/windows/**.cc"
		}
	
	filter "configurations:devel"
		runtime "debug"
		symbols "on"
		defines
		{
			"TL_BUILD_DEVEL",
			"TL_TEST_BUILD"
		}
	
	filter "configurations:prev"
		runtime "release"
		optimize "speed"
		defines
		{
			"TL_BUILD_PREV",
			"TL_TEST_BUILD"
		}
	
	filter "configurations:dist"
		runtime "release"
		optimize "speed"
		defines
		{
			"TL_BUILD_DIST"
		}
	