group "RedEngine"

function RedEngineLib( name )
	project(name)
		kind("StaticLib")
		language("C++")
		cppdialect(cppDialect)

		RedDefaultProjectOptions()
		
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
end

RedEngineLib("RedEngineLib")
	files
	{
		enginePath .. "/compile.cpp",
		
	}

-- Project used to reference all the files of the engine projet so IDE are not lost
RedEngineLib("RedEngineLib_AllFiles")
	files
	{
		enginePath .. "/include/**.hpp",
		enginePath .. "/src/**.cpp",
	}

	removefiles
	{
		enginePath .. "/compile.cpp",
	}

