workspace "Triangl"
	architecture "x64"
	configurations
	{
		"Development",
		"Preview",
		"Shipping"
	}
	startproject "Sandbox"

include "Dependencies.lua"

group "Engine/ThirdParty"
	include "ThirdParty/GLFW"
	include "ThirdParty/Glad"
group ""
group "Engine"
	include "Engine"
group ""
group "Templates"
	include "Sandbox"
group ""
