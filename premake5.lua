include "Dependencies.lua"
workspace "MangaList"
	startproject "MangaList"

	platforms
	{
		"x64",
		"x86"
	}

	system
	(
		"Windows",
		"Unix"
	)

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

	filter "platforms:x64"
		architecture "x64"
	
	filter "platforms:x86"
		architecture "x86"

	filter "system:Windows"
		system "windows"
		
	filter "system:Unix"
		system "linux"

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

group "Dependencies"

--Libs
include "MangaList/vendor/yaml-cpp"
include "GUI/vendor/glfw"		
include "GUI/vendor/imgui"		

group ""

--Projects
include "MangaList"
include "GUI"
--include "Sandbox"