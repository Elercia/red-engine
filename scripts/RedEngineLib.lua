group "RedEngine"
project "RedEngineLib"
	kind("StaticLib")
	language("C++")
	cppdialect(cppDialect)

	RedDefaultProjectOptions()
	
	files
	{
		enginePath .. "/compile.cpp",
		
	}

	includedirs
	{
		enginePath .. "/include/",
		enginePath .. "/src/",
		ExternalIncludeDirs,
	}

	defines
	{
		"RED_USE_PROFILER",
		"FMT_EXCEPTIONS=0",
	}

	links
	{
		libsToLink
	}

	libdirs
	{
		ExternalLibDirs
	}

	filter{ "platforms:Linux64" }
  		buildoptions {}
	filter {}

	filter { "toolset:msc" }
		linkoptions 
		{
			"/NODEFAULTLIB:library"
		}
	filter {}

	filter { "platforms:Win64" }
		systemversion "latest"

		defines
		{
			"RED_WINDOWS"
		}

		links
		{
			"SDL2main.lib"
		}
	filter {}

	filter { "platforms:Linux64" }
		defines
		{
			"RED_LINUX"
		}
	filter {}

	filter { "configurations:Debug" }
		defines {"RED_DEBUG", "RED_BREAK_ON_ASSERT" }
		runtime "Debug"
		symbols "Full"
	filter {}

	filter { "configurations:Release" }
		defines "RED_RELEASE"
		runtime "Release"
		optimize "on"
	filter {}
