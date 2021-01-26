project "Template"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	location("projects")
	targetdir ("%{rootPath}/output/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{rootPath}/output/obj/" .. outputdir .. "/%{prj.name}")

	-- pchheader "hzpch.h"
	-- pchsource "src/hzpch.cpp"

	PongPath = "%{rootPath}/templates/Pong"

	files
	{
		"%{PongPath}/include/**.hpp",
		"%{PongPath}/src/**.cpp",
	}

	includedirs
	{
		"%{PongPath}/include/",
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
		"RedEngineLib",
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"RED_WINDOWS"
		}

	filter "system:linux"
		defines
		{
			"RED_LINUX"
		}

	filter "configurations:Debug"
		defines "RED_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "RED_RELEASE"
		runtime "Release"
		optimize "on"

	filter ""

	flags { "NoPCH" }
