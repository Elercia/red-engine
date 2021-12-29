group "RedEngine"
project "RedEngineLib"
	kind("StaticLib")
	language("C++")
	cppdialect(cppDialect)

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
		-- "RED_USE_PROFILER",
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
  		buildoptions { "" }
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

		linkoptions 
		{
			"/NODEFAULTLIB:library"
		}
	filter {}

	filter { "platforms:Linux64" }
		defines
		{
			"RED_LINUX"
		}
	filter {}

	filter { "configurations:Debug" }
		defines "RED_DEBUG"
		runtime "Debug"
		symbols "on"
	filter {}

	filter { "configurations:Release" }
		defines "RED_RELEASE"
		runtime "Release"
		optimize "on"
	filter {}
