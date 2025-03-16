workspace "triangl"
	architecture "x64"
	configurations
	{
		"devel",
		"prev",
		"dist"
	}
	startproject "sandbox"

include "premakedeps.lua"

group "engine"
	include "engine"
group ""
group "templates"
	include "sandbox"
group ""
