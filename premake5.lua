workspace "Lithe"
	architecture "x86_64"
	startproject "Sandbox"
	
	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

	flags
	{
		"MultiProcessorCompile"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["GLFW"] = "Lithe/vendor/GLFW/include"
IncludeDir["Glad"] = "Lithe/vendor/Glad/include"
IncludeDir["ImGui"] = "Lithe/vendor/imgui"
IncludeDir["glm"] = "Lithe/vendor/glm"
IncludeDir["stb_image"] = "Lithe/vendor/stb_image"

group "Dependencies"
    include "Lithe/vendor/GLFW"
    include "Lithe/vendor/Glad"
    include "Lithe/vendor/imgui"
group ""

project "Lithe"
	location "Lithe"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

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
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl",
		"%{prj.name}/vendor/stb_image/**.h",
		"%{prj.name}/vendor/stb_image/**.cpp"
	}

	defines
	{
		"_CRT_SECURE_NO_WARNINGS"
	}

	includedirs
	{
		"%{prj.name}/vendor/spdlog/include",
		"%{prj.name}/src",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.stb_image}"
	}

	links
	{
		"GLFW",
		"opengl32.lib",
		-- "dwmapi.lib",
		"Glad",
		"ImGui"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"LI_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}

		-- postbuildcommands
		-- {
		-- 	("IF NOT EXIST \"%{wks.location}/bin/" .. outputdir .. "/Sandbox\" (mkdir \"%{wks.location}/bin/" .. outputdir .. "/Sandbox\")"),
		-- 	("{COPYFILE} \"%{cfg.buildtarget.abspath}\" \"%{wks.location}/bin/" .. outputdir .. "/Sandbox/Lithe.dll\"")
		-- }

	filter "configurations:Debug"
		defines "LI_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "LI_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "LI_DIST"
		runtime "Release"
		optimize "on"

project "Lithium"
	location "Lithium"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

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
		"Lithe/src",
		"Lithe/vendor",
		"%{prj.name}/src",
		"%{IncludeDir.glm}"
	}

	links
	{
		"Lithe"
	}

	filter "system:windows"
		staticruntime "On"
		systemversion "latest"

	filter "configurations:Debug"
		defines "LI_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "LI_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "LI_DIST"
		kind "WindowedApp"
		runtime "Release"
		optimize "on"
		linkoptions { "/ENTRY:mainCRTStartup" }

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

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
		"Lithe/src",
		"Lithe/vendor",
		"%{prj.name}/src",
		"%{IncludeDir.glm}"
	}

	links
	{
		"Lithe"
	}

	filter "system:windows"
		staticruntime "On"
		systemversion "latest"

	filter "configurations:Debug"
		defines "LI_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "LI_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "LI_DIST"
		kind "WindowedApp"
		runtime "Release"
		optimize "on"
		linkoptions { "/ENTRY:mainCRTStartup" }