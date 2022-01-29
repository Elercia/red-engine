group("Tests")

project ("RedEngineTest")
	kind "ConsoleApp"
	language("C++")
	
	rtti("Off")
	cppdialect(cppDialect)
	warnings("Extra")
	flags("NoPCH")
	staticruntime("Off")

	targetdir(rootPath .. "/output/bin/" .. outputDirSementic)
	objdir(rootPath .. "/output/obj/" .. outputDirSementic)

	location(projectsFilesLocation)

	local testPath = rootPath .. "test/"
	files {
		testPath .. "src/**.cpp",
		testPath .. "include/**.hpp",
		externalDirectoryPath .. "/Catch2/src/*.cpp"
	}

	includedirs
	{
		enginePath .. "include/",
		testPath .. "include/",
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

	filter "configurations:Debug"
		defines "RED_DEBUG"
		runtime "Debug"
		symbols "Full"
	filter {}

	filter "configurations:Release"
		defines "RED_RELEASE"
		runtime "Release"
		optimize "on"
		symbols "on"
	filter {}

	postbuildcommands { "{COPY} %{cfg.buildtarget.directory}/* " .. rootPath .. "test" }