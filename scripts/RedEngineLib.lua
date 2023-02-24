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

	links
	{
		libsToLink
	}

	libdirs
	{
		ExternalLibDirs
	}