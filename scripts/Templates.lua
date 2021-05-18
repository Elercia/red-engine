function TemplateProject(Name)
	print("Template Project : " .. Name)
	
	group("Template")
	project(Name)
	kind("ConsoleApp")
	language("C++")
	cppdialect("C++17")
	
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
		"SDL2_image",
		"Box2D",
		"fmt",
		"fmod",
		"fsbank",
		"fmodstudio",
		"optick",
	}

	defines
	{
		"RED_USE_PROFILER",
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"RED_WINDOWS"
		}

		links
		{
			"SDL2main",
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

	filter {}
end

TemplateProject("Pong")