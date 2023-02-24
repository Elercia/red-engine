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

	postbuildcommands { "{COPY} \"%{cfg.buildtarget.abspath}\" \"" .. rootPath .. "test\"" }
