OutputDir = {}
OutputDir["__Completer__"] = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
OutputDir["Binaries"] = "%{wks.location}/Binaries/%{OutputDir.__Completer__}"
OutputDir["Intermediates"] = "%{wks.location}/Binaries-Int/%{OutputDir.__Completer__}"

ThirdParty = "%{wks.location}/ThirdParty"

ProjectDir = {}
ProjectDir["Triangl"] = "%{wks.location}/Engine"
ProjectDir["Sandbox"] = "%{wks.location}/Sandbox"
ProjectDir["GLFW"] = "%{ThirdParty}/GLFW"
ProjectDir["Glad"] = "%{ThirdParty}/Glad"

IncludeDir = {}
IncludeDir["Triangl"] = "%{ProjectDir.Triangl}/Source"
IncludeDir["Sandbox"] = "%{ProjectDir.Sandbox}/Source"
IncludeDir["fmt"] = "%{ThirdParty}/fmt/include"
IncludeDir["spdlog"] = "%{ThirdParty}/spdlog/include"
IncludeDir["glm"] = "%{ThirdParty}/glm"
IncludeDir["GLFW"] = "%{ProjectDir.GLFW}/include"
IncludeDir["Glad"] = "%{ProjectDir.Glad}/include"
