group("Tests")

project ("RedEngineTest")
	kind "ConsoleApp"
	language("C++")
	
	RedDefaultProjectOptions()

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
		"glm",
		libsToLink
	}

	defines
	{
		"FMT_EXCEPTIONS=0",
	}

	filter "configurations:Debug"
		defines {"RED_DEBUG", "RED_BREAK_ON_ASSERT" }
		runtime "Debug"
		symbols "Full"
	filter {}

	filter "configurations:Release"
		defines "RED_RELEASE"
		runtime "Release"
		optimize "on"
		symbols "on"
	filter {}

	postbuildcommands { "{COPY} \"%{cfg.buildtarget.directory}/*\" \"" .. rootPath .. "test\"" }