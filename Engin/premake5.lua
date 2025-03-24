project "Triangl"
	language "C++"
	cppdialect "C++17"
	kind "StaticLib"
	
	targetdir "%{OutputDir.Binaries}/%{prj.name}"
	objdir    "%{OutputDir.Intermediates}/%{prj.name}"
	
	pchheader "TrianglPCH.h"
	pchsource "Source/TrianglPCH.cpp"

	files
	{
		"Source/**.h",
		"Source/**.cpp"
	}
	
	includedirs
	{
		"Source/Engine",
		"Source",
		
		"%{IncludeDir.fmt}",
		"%{IncludeDir.spdlog}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}"
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
			"Source/Platform/Linux/**.cpp"
		}

	filter "system:linux"
		defines
		{
			"TL_PLATFORM_LINUX"
		}
		excludes
		{
			"Source/Platform/Windows/**.cpp"
		}
	
	filter "configurations:Development"
		runtime "Debug"
		symbols "On"
		defines
		{
			"TL_DEVELOPMENT",
			"TL_TEST_BUILD"
		}
	
	filter "configurations:Preview"
		runtime "Release"
		optimize "Speed"
		defines
		{
			"TL_PREVIEW",
			"TL_TEST_BUILD"
		}
	
	filter "configurations:Shipping"
		runtime "Release"
		optimize "Speed"
		defines
		{
			"TL_SHIPPING"
		}
	