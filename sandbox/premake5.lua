project "sandbox"
	language "c++"
	cppdialect "c++17"
	
	targetdir "%{outdir.bin}/%{prj.name}"
	objdir    "%{outdir.obj}/%{prj.name}"
	
	files
	{
		"src/**.hh",
		"src/**.cc"
	}
	
	includedirs
	{
		"%{incdir.triangl}",
		"src",
		
		"%{incdir.fmt}",
		"%{incdir.spdlog}",
		"%{incdir.glm}"
	}
	
	links
	{
		"triangl"
	}
	
	filter "system:windows"
		systemversion "latest"
		defines
		{
			"TL_PLATFORM_WINDOWS",

			"_CRT_SECURE_NO_WARNINGS",
			"_SILENCE_ALL_MS_EXT_DEPRECATION_WARNINGS"
		}
	
	filter "system:linux"
		defines
		{
			"TL_PLATFORM_LINUX"
		}
	
	filter "configurations:devel"
		runtime "debug"
		symbols "on"
		kind "consoleapp"
		defines
		{
			"TL_BUILD_DEVEL",
			"TL_TEST_BUILD"
		}
	
	filter "configurations:prev"
		runtime "release"
		optimize "speed"
		kind "consoleapp"
		defines
		{
			"TL_BUILD_PREV",
			"TL_TEST_BUILD"
		}
	
	filter "configurations:dist"
		runtime "release"
		optimize "speed"
		kind "windowedapp"
		defines
		{
			"TL_BUILD_DIST"
		}
	