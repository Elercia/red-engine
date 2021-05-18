group "RedEngine"
project "RedEngineLib"
	kind("StaticLib")
	language("C++")
	cppdialect("C++17")

	rtti("Off")
	exceptionhandling("Off")
	warnings("Extra")
	flags("NoPCH")
	staticruntime("Off")

	location(projectsFilesLocation)
	targetdir(rootPath .. "/output/bin/" .. outputDirSementic)
	objdir(rootPath .. "/output/obj/" .. outputDirSementic)

	files
	{
		enginePath .. "/include/**.hpp",
		enginePath .. "/include/**.inl",
		enginePath .. "/src/**.cpp",
		
	}

	includedirs
	{
		enginePath .. "/include/",
		ExternalIncludeDirs,
	}

	defines
	{
		"RED_USE_PROFILER",
	}

	links
	{
		"SDL2",
		"SDL2_image",
		"Box2D",
		"fmt",
		"fmod",
		"fsbank",
		"fmodstudio",
		"optick",
	}

	libdirs
	{
		ExternalLibDirs
	}

	configuration { "linux", "gmake" }
  		buildoptions { "`wx-config --cxxflags`", "-ansi", "-pedantic" }

	configuration { "vs2019" }
  		buildoptions { "" }

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"RED_WINDOWS"
		}

		links
		{
			"SDL2main.lib"
		}

		linkoptions 
		{
			"/NODEFAULTLIB:library"
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

	filter "configurations:Release"
		defines "RED_RELEASE"
		runtime "Release"
		optimize "on"

	filter {}
