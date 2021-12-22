project "GUI"
	kind "ConsoleApp"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "../MangaList/core/pch.h"
	pchsource ("../MangaList/src/core/pch.cpp")
	
	files 
	{
		"src/**.h",
		"src/**.c",
		"src/**.cpp",
	}


	includedirs
	{
		"src/",
		"%{IncludeDirectories.yaml}",
		"%{IncludeDirectories.spdlog}",
		"%{IncludeDirectories.debugbreak}",
		"%{IncludeDirectories.glfw}",
		"%{IncludeDirectories.imgui}",

	}

	links
	{
		"yaml-cpp",
		"ImGui",
		"GLFW"
	}

	postbuildcommands
	{
		("{COPYDIR} \"./src/**.h\" \"./include/GUI\""),
	}

	filter "system:Windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"MLIST_GUI_WINDOWS_BUILD",
			"MLIST_GUI_STATIC_BUILD"
		}

	filter "system:Unix"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"MLIST_GUI_UNIX_BUILD",
			"MLIST_GUI_STATIC_BUILD"
		}

	filter "configurations:Debug"
		defines "MLIST_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "MLIST_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "MLIST_DIST"
		optimize "On"

	--filter { "system:windows", "configurations:Debug" }
	--	buildoptions "/MTd"
	--
	--filter { "system:windows", "configurations:Release" }
	--	buildoptions "/MT"
	--
	--filter { "system:windows", "configurations:Dist" }
	--	buildoptions "/MT"