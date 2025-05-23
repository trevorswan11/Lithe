project "Lithe"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "off"

	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "lipch.h"
	pchsource "src/lipch.cpp"

	filter "action:vs*"
		buildoptions { "/utf-8" }

	files
	{
		"src/**.h",
		"src/**.hpp",
		"src/**.c",
		"src/**.cpp",
		"vendor/glm/glm/**.hpp",
		"vendor/glm/glm/**.inl",
		"vendor/stb_image/**.h",
		"vendor/stb_image/**.cpp",
		"vendor/ImGuizmo/ImGuizmo.h",
		"vendor/ImGuizmo/ImGuizmo.cpp",
		"vendor/miniaudio/miniaudio.h",
		"vendor/miniaudio/miniaudio.c"
	}

	defines
	{
		"_CRT_SECURE_NO_WARNINGS",
		"GLFW_INCLUDE_NONE"
	}

	includedirs
	{
		"src",
		"vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.stb_image}",
		"%{IncludeDir.entt}",
		"%{IncludeDir.yaml_cpp}",
		"%{IncludeDir.ImGuizmo}",
		"%{IncludeDir.Box2D}",
		"%{IncludeDir.VulkanSDK}",
		"%{IncludeDir.msdfgen}",
 		"%{IncludeDir.msdf_atlas_gen}",
		"%{IncludeDir.mono}",
		"%{IncludeDir.filewatch}",
		"%{IncludeDir.miniaudio}"
	}

	links
	{
		"GLFW",
		"Box2D",
		"opengl32.lib",
		"yaml-cpp",
		"Glad",
		"ImGui",
		"msdf-atlas-gen",
		"%{Library.mono}"
	}

	filter "files:vendor/ImGuizmo/**.cpp"
		flags { "NoPCH" }

	filter "files:vendor/miniaudio/**.c"
		flags { "NoPCH" }

	filter "system:windows"
		systemversion "latest"

		defines
		{
		}

		links
 		{
 			"%{Library.WinSock}",
 			"%{Library.WinMM}",
 			"%{Library.WinVersion}",
 			"%{Library.BCrypt}",
 		}

		linkoptions { "/IGNORE:4006" }

	filter "configurations:Debug"
		defines "LI_DEBUG"
		runtime "Debug"
		symbols "on"

		links
 		{
 			"%{Library.ShaderC_Debug}",
 			"%{Library.SPIRV_Cross_Debug}",
 			"%{Library.SPIRV_Cross_GLSL_Debug}"
 		}

	filter "configurations:Release"
		defines "LI_RELEASE"
		runtime "Release"
		optimize "on"

		links
		{
			"%{Library.ShaderC_Release}",
			"%{Library.SPIRV_Cross_Release}",
			"%{Library.SPIRV_Cross_GLSL_Release}"
		}

	filter "configurations:Dist"
		defines "LI_DIST"
		runtime "Release"
		optimize "on"

		links
 		{
 			"%{Library.ShaderC_Release}",
 			"%{Library.SPIRV_Cross_Release}",
 			"%{Library.SPIRV_Cross_GLSL_Release}"
 		}
