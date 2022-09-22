function TemplateProject(Name)
	print("Template Project : " .. Name)
	
	group("Template")
	project(Name)
	kind("ConsoleApp")
	language("C++")
	cppdialect(cppDialect)
	
	rtti("Off")
	exceptionhandling("Off")
	warnings("Everything")
	flags("NoPCH")
	staticruntime("Off")

	location(projectsFilesLocation)
	targetdir(rootPath .. "/output/bin/" .. outputDirSementic)
	objdir (rootPath .. "/output/obj/" .. outputDirSementic)

	local templatePath = rootPath .. "/templates/"..Name

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
		libsToLink
	}

	defines
	{
		"RED_USE_PROFILER",
		"FMT_EXCEPTIONS=0",
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
		defines {"RED_DEBUG", "RED_BREAK_ON_ASSERT" }
		runtime "Debug"
		symbols "on"
	filter {}

	filter "configurations:Release"
		defines "RED_RELEASE"
		runtime "Release"
		optimize "on"
		symbols "on"
	filter {}

	postbuildcommands { "{COPY} %{cfg.buildtarget.directory}/* " .. rootPath .. "templates/%{prj.name}" }
end

TemplateProject("Pong")
TemplateProject("Perf")