include "./vendor/premake/premake_customization/solution_items.lua"

workspace "Lithe"
	architecture "x86_64"
	startproject "Lithium"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

	solution_items
	{
		".editorconfig"
	}

	flags
	{
		"MultiProcessorCompile"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["GLFW"] = "%{wks.location}/Lithe/vendor/GLFW/include"
IncludeDir["Glad"] = "%{wks.location}/Lithe/vendor/Glad/include"
IncludeDir["ImGui"] = "%{wks.location}/Lithe/vendor/imgui"
IncludeDir["glm"] = "%{wks.location}/Lithe/vendor/glm"
IncludeDir["stb_image"] = "%{wks.location}/Lithe/vendor/stb_image"
IncludeDir["entt"] = "%{wks.location}/Lithe/vendor/entt/include"
IncludeDir["yaml_cpp"] = "%{wks.location}/Lithe/vendor/yaml-cpp/include"
IncludeDir["ImGuizmo"] = "%{wks.location}/Lithe/vendor/ImGuizmo"

group "Dependencies"
	include "vendor/premake"
	include "Lithe/vendor/GLFW"
	include "Lithe/vendor/Glad"
	include "Lithe/vendor/imgui"
	include "Lithe/vendor/yaml-cpp"
group ""

include "Lithe"
include "Sandbox"
include "Lithium"