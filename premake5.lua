workspace "Lithe"
	architecture "x64"
	startproject "Sandbox"
	
	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["GLFW"] = "Lithe/vendor/GLFW/include"
IncludeDir["Glad"] = "Lithe/vendor/Glad/include"
IncludeDir["ImGui"] = "Lithe/vendor/imgui"

include "Lithe/vendor/GLFW"
include "Lithe/vendor/Glad"
include "Lithe/vendor/imgui"

project "Lithe"
	location "Lithe"
	kind "SharedLib"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "lipch.h"
	pchsource "Lithe/src/lipch.cpp"

	filter "action:vs*"
		buildoptions { "/utf-8" }

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
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}"
	}

	links
	{
		"GLFW",
		"opengl32.lib",
		"dwmapi.lib",
		"Glad",
		"ImGui"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"LI_PLATFORM_WINDOWS",
			"LI_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}

		postbuildcommands
		{
			("IF NOT EXIST \"%{wks.location}/bin/" .. outputdir .. "/Sandbox\" (mkdir \"%{wks.location}/bin/" .. outputdir .. "/Sandbox\")"),
			("{COPYFILE} \"%{cfg.buildtarget.abspath}\" \"%{wks.location}/bin/" .. outputdir .. "/Sandbox/Lithe.dll\"")
		}

	filter "configurations:Debug"
		defines "LI_DEBUG"
		buildoptions "/MDd"
		symbols "On"

	filter "configurations:Release"
		defines "LI_RELEASE"
		buildoptions "/MD"
		optimize "On"

	filter "configurations:Dist"
		defines "LI_DIST"
		buildoptions "/MD"
		optimize "On"
		
project "GLFW"
	kind "StaticLib"
	language "C"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"Lithe/vendor/GLFW/include/GLFW/glfw3.h",
		"Lithe/vendor/GLFW/include/GLFW/glfw3native.h",
		"Lithe/vendor/GLFW/src/internal.h",
		"Lithe/vendor/GLFW/src/platform.h",
		"Lithe/vendor/GLFW/src/mappings.h",
		"Lithe/vendor/GLFW/src/context.c",
		"Lithe/vendor/GLFW/src/init.c",
		"Lithe/vendor/GLFW/src/input.c",
		"Lithe/vendor/GLFW/src/monitor.c",
		"Lithe/vendor/GLFW/src/platform.c",
		"Lithe/vendor/GLFW/src/vulkan.c",
		"Lithe/vendor/GLFW/src/window.c",
		"Lithe/vendor/GLFW/src/egl_context.c",
		"Lithe/vendor/GLFW/src/osmesa_context.c",
		"Lithe/vendor/GLFW/src/null_platform.h",
		"Lithe/vendor/GLFW/src/null_joystick.h",
		"Lithe/vendor/GLFW/src/null_init.c",

		"Lithe/vendor/GLFW/src/null_monitor.c",
		"Lithe/vendor/GLFW/src/null_window.c",
		"Lithe/vendor/GLFW/src/null_joystick.c"
	}

	filter "system:windows"
		systemversion "latest"
		staticruntime "On"

		files
		{
			"Lithe/vendor/GLFW/src/win32_init.c",
			"Lithe/vendor/GLFW/src/win32_module.c",
			"Lithe/vendor/GLFW/src/win32_joystick.c",
			"Lithe/vendor/GLFW/src/win32_monitor.c",
			"Lithe/vendor/GLFW/src/win32_time.h",
			"Lithe/vendor/GLFW/src/win32_time.c",
			"Lithe/vendor/GLFW/src/win32_thread.h",
			"Lithe/vendor/GLFW/src/win32_thread.c",
			"Lithe/vendor/GLFW/src/win32_window.c",
			"Lithe/vendor/GLFW/src/wgl_context.c",
			"Lithe/vendor/GLFW/src/egl_context.c",
			"Lithe/vendor/GLFW/src/osmesa_context.c"
		}

		defines
		{
			"_GLFW_WIN32",
			"_CRT_SECURE_NO_WARNINGS"
		}

	filter "configurations:Debug"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		runtime "Release"
		optimize "on"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"

	dependson { "Lithe" }

	filter "action:vs*"
		buildoptions { "/utf-8" }

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
		buildoptions "/MDd"
		symbols "On"

	filter "configurations:Release"
		defines "LI_RELEASE"
		buildoptions "/MD"
		optimize "On"

	filter "configurations:Dist"
		defines "LI_DIST"
		buildoptions "/MD"
		optimize "On"
