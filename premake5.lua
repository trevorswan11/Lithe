include "./vendor/premake/premake_customization/solution_items.lua"
include "Dependencies.lua"

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