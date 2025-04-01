project "Lithium"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "off"

	dependson { "Lithe" }

	filter "action:vs*"
		buildoptions { "/utf-8" }

	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"src/**.h",
		"src/**.hpp",
		"src/**.c",
		"src/**.cpp"
	}

	includedirs
	{
		"src",
		"%{wks.location}/Lithe/vendor/spdlog/include",
		"%{wks.location}/Lithe/src",
		"%{wks.location}/Lithe/vendor",
		"%{IncludeDir.glm}",
		"%{IncludeDir.entt}",
		"%{IncludeDir.ImGuizmo}"
	}

	links
	{
		"Lithe"
	}

	filter "system:windows"
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