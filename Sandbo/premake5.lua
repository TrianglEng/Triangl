project "Sandbox"
	language "C++"
	cppdialect "C++17"
	
	targetdir "%{OutputDir.Binaries}/%{prj.name}"
	objdir    "%{OutputDir.Intermediates}/%{prj.name}"
	
	files
	{
		"Source/**.h",
		"Source/**.cpp"
	}
	
	includedirs
	{
		"%{IncludeDir.Triangl}/Engine",
		"%{IncludeDir.Triangl}",
		"Source",
		
		"%{IncludeDir.fmt}",
		"%{IncludeDir.spdlog}",
		"%{IncludeDir.glm}"
	}
	
	links
	{
		"Triangl",

		"GLFW",
		"Glad"
	}
	
	filter "system:windows"
		systemversion "latest"
		defines
		{
			"TL_PLATFORM_WINDOWS",

			"_CRT_SECURE_NO_WARNINGS",
			"_SILENCE_ALL_MS_EXT_DEPRECATION_WARNINGS"
		}
		links
		{
			"dwmapi.lib"
		}
	
	filter "system:linux"
		defines
		{
			"TL_PLATFORM_LINUX"
		}
	
	filter "configurations:Development"
		runtime "Debug"
		symbols "On"
		kind "ConsoleApp"
		defines
		{
			"TL_DEVELOPMENT",
			"TL_TEST_BUILD"
		}
	
	filter "configurations:Preview"
		runtime "Release"
		optimize "Speed"
		kind "ConsoleApp"
		defines
		{
			"TL_PREVIEW",
			"TL_TEST_BUILD"
		}
	
	filter "configurations:Shipping"
		runtime "Release"
		optimize "Speed"
		kind "WindowedApp"
		defines
		{
			"TL_SHIPPING"
		}
	