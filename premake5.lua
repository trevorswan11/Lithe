workspace "Lithe"
	architecture "x64"
	
	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["GLFW"] = "Lithe/vendor/GLFW/include"

include "Lithe/vendor/GLFW"

project "Lithe"
	location "Lithe"
	kind "SharedLib"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "lipch.h"
	pchsource "Lithe/src/lipch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.hpp",
		"%{prj.name}/src/**.c",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"%{prj.name}/vendor/spdlog/include",
		"%{prj.name}/src",
		"%{IncludeDir.GLFW}"
	}

	links
	{
		"GLFW",
		"opengl32.lib",
		"dwmapi.lib"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"LI_PLATFORM_WINDOWS",
			"LI_BUILD_DLL"
		}

		postbuildcommands
		{
			("IF NOT EXIST \"%{wks.location}/bin/" .. outputdir .. "/Sandbox\" (mkdir \"%{wks.location}/bin/" .. outputdir .. "/Sandbox\")"),
			("{COPYFILE} \"%{cfg.buildtarget.abspath}\" \"%{wks.location}/bin/" .. outputdir .. "/Sandbox/Lithe.dll\"")
		}

	filter "configurations:Debug"
		defines "LI_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "LI_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "LI_DIST"
		optimize "On"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"

	dependson { "Lithe" }

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.hpp",
		"%{prj.name}/src/**.c",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"Lithe/vendor/spdlog/include",
		"Lithe/src"
	}

	links
	{
		"Lithe"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"LI_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "LI_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "LI_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "LI_DIST"
		optimize "On"