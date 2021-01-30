group "RedEngine"
project "RedEngineLib"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	location("projects")
	targetdir ("%{rootPath}/output/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{rootPath}/output/obj/" .. outputdir .. "/%{prj.name}")

	-- pchheader "hzpch.h"
	-- pchsource "src/hzpch.cpp"

	enginePath = "%{rootPath}/engine"

	files
	{
		"%{enginePath}/include/**.hpp",
		"%{enginePath}/src/**.cpp",
	}

	includedirs
	{
		"%{enginePath}/include/",
		"%{IncludeDir.DebugBreak}",
		"%{IncludeDir.FmodCore}",
		"%{IncludeDir.FmodFsBank}",
		"%{IncludeDir.FmodStudio}",
		"%{IncludeDir.optick}",
		"%{IncludeDir.SDL2}",
		"%{IncludeDir.SDL2_internal}",
		"%{IncludeDir.SDL_image}",
		"%{IncludeDir.nlohmann_json}",
		"%{IncludeDir.fmt}",
		"%{IncludeDir.Box2D}",
	}

	defines
	{
		"RED_USE_PROFILER",
	}

	links
	{
		"SDL2",
		"SDL2main",
	}

	libdirs
	{
		"%{IncludeDir.SDL2}",
	}

	rtti("Off")
	exceptionhandling("Off")
	warnings("Extra")
	flags("NoPCH")

	configuration { "linux", "gmake" }
  		buildoptions { "`wx-config --cxxflags`", "-ansi", "-pedantic" }

	configuration { "vs2019" }
  		buildoptions { "" }

	filter "system:Windows"
		systemversion "latest"

		defines
		{
			"RED_WINDOWS"
		}

		links
		{
			enginePath .. "/../external/SDL2/lib/x64/SDL2*.*"
		}

	filter "system:Linux"
		defines
		{
			"RED_LINUX"
		}

	filter "configurations:Debug"
		defines "RED_DEBUG"
		runtime "Debug"
		symbols "on"
		optimize "Off"

	filter "configurations:Release"
		defines "RED_RELEASE"
		runtime "Release"
		optimize "Speed"

	filter ""
