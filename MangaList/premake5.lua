project "MangaList"
	kind "ConsoleApp"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "core/pch.h"
	pchsource ("src/core/pch.cpp")
	

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
		"%{IncludeDirectories.spdlog}"
	}

	links
	{
		"yaml-cpp"
	}

	postbuildcommands
	{
		("{COPYDIR} \"./src/**.h\" \"./include/MangaList\""),
	}

	filter "system:Windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"MLIST_WINDOWS_BUILD",
			"MLIST_STATIC_BUILD"
		}

	filter "system:Unix"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"MLIST_UNIX_BUILD",
			"MLIST_STATIC_BUILD"
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