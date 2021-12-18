function TemplateProject(Name)
	print("Template Project : " .. Name)
	
	group("Template")
	project(Name)
	kind("ConsoleApp")
	language("C++")
	cppdialect(cppDialect)
	
	rtti("Off")
	exceptionhandling("Off")
	warnings("Extra")
	flags("NoPCH")
	staticruntime("Off")

	location(projectsFilesLocation)
	targetdir(rootPath .. "/output/bin/" .. outputDirSementic)
	objdir (rootPath .. "/output/obj/" .. outputDirSementic)

	local templatePath = rootPath .. "/templates/Pong"

	files
	{
		templatePath .. "/src/**.hpp",
		templatePath .. "/src/**.inl",
		templatePath .. "/src/**.cpp",
	}

	includedirs
	{
		templatePath .. "/include/",
		enginePath .. "/include/",
		ExternalIncludeDirs,
	}

	libdirs
	{
		ExternalLibDirs
	}

	links
	{
		"RedEngineLib",
		"SDL2",
		"Box2D",
		"fmt",
		"fmod",
		"fsbank",
		"fmodstudio",
		"optick",
		"GL3W",
	}

	defines
	{
		-- "RED_USE_PROFILER",
	}

	filter "platforms:Win64"
		systemversion "latest"

		defines
		{
			"RED_WINDOWS"
		}

		links
		{
			"SDL2main",
		}
	filter {}

	filter "platforms:Linux64"
		defines
		{
			"RED_LINUX"
		}
	filter {}

	filter "configurations:Debug"
		defines "RED_DEBUG"
		runtime "Debug"
		symbols "on"
	filter {}

	filter "configurations:Release"
		defines "RED_RELEASE"
		runtime "Release"
		optimize "on"
		symbols "on"
	filter {}
end

TemplateProject("Pong")