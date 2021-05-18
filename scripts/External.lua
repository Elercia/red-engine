-- Include directories relative to root folder (solution directory)
externalDirectoryPath= rootPath .. "external"

ExternalIncludeDirs = {}
ExternalLibDirs = {}

--------------------------------------------------------------
-------------- Precompiled / header only LIBS ----------------
--------------------------------------------------------------

-- SDL2 
if os.istarget("windows") then
	table.insert(ExternalIncludeDirs, externalDirectoryPath .. "/SDL2/include")
	table.insert(ExternalIncludeDirs, externalDirectoryPath .. "/SDL2/include/SDL2")
	table.insert(ExternalLibDirs, externalDirectoryPath .. "/SDL2/lib/x64")

	filter { "system:windows" }
		postbuildcommands { "{COPY} ../../../external/SDL2/lib/x64/SDL2.dll %{cfg.buildtarget.directory}" }	
	filter {}

	-- SDL Image
	table.insert(ExternalIncludeDirs, externalDirectoryPath .. "/SDL_image/include")
	table.insert(ExternalLibDirs, externalDirectoryPath .. "/SDL_image/lib/x64")

	filter { "system:windows" }
		postbuildcommands { "{COPY} ../../../external/SDL_image/lib/x64/libjpeg-9.dll %{cfg.buildtarget.directory}" }
		postbuildcommands { "{COPY} ../../../external/SDL_image/lib/x64/libpng16-16.dll %{cfg.buildtarget.directory}" }
		postbuildcommands { "{COPY} ../../../external/SDL_image/lib/x64/libtiff-5.dll %{cfg.buildtarget.directory}" }
		postbuildcommands { "{COPY} ../../../external/SDL_image/lib/x64/libwebp-7.dll %{cfg.buildtarget.directory}" }
		postbuildcommands { "{COPY} ../../../external/SDL_image/lib/x64/SDL2_image.dll %{cfg.buildtarget.directory}" }
		postbuildcommands { "{COPY} ../../../external/SDL_image/lib/x64/zlib1.dll %{cfg.buildtarget.directory}" }
	filter {}
end


-- DebugBreak (Header only)
table.insert(ExternalIncludeDirs, externalDirectoryPath .. "/DebugBreak")

-- FMOD 
table.insert(ExternalIncludeDirs, externalDirectoryPath .. "/Fmod/core/inc")
table.insert(ExternalIncludeDirs, externalDirectoryPath .. "/Fmod/fsbank/inc")
table.insert(ExternalIncludeDirs, externalDirectoryPath .. "/Fmod/studio/inc")

if os.istarget("windows") then
	table.insert(ExternalLibDirs, externalDirectoryPath .. "/Fmod/core/lib/x64")
	table.insert(ExternalLibDirs, externalDirectoryPath .. "/Fmod/fsbank/lib/x64")
	table.insert(ExternalLibDirs, externalDirectoryPath .. "/Fmod/studio/lib/x64")
elseif os.istarget("linux") then
	table.insert(ExternalLibDirs, externalDirectoryPath .. "/Fmod/core/lib/x86_64")
	table.insert(ExternalLibDirs, externalDirectoryPath .. "/Fmod/fsbank/lib/x86_64")
	table.insert(ExternalLibDirs, externalDirectoryPath .. "/Fmod/studio/lib/x86_64")
end

if os.istarget("windows") then
	filter { "system:windows" }
		postbuildcommands { "{COPY} ../../../external/Fmod/core/lib/x64/fmod.dll %{cfg.buildtarget.directory}" }
		postbuildcommands { "{COPY} ../../../external/Fmod/fsbank/lib/x64/fsbank.dll %{cfg.buildtarget.directory}" }
		postbuildcommands { "{COPY} ../../../external/Fmod/fsbank/lib/x64/libfsbvorbis64.dll %{cfg.buildtarget.directory}" }
		postbuildcommands { "{COPY} ../../../external/Fmod/fsbank/lib/x64/opus.dll %{cfg.buildtarget.directory}" }
		postbuildcommands { "{COPY} ../../../external/Fmod/studio/lib/x64/fmodstudio.dll %{cfg.buildtarget.directory}" }
	filter {}
end

-- Json
table.insert(ExternalIncludeDirs, externalDirectoryPath .. "/nlohmann_json/single_include")

-- Catch2
table.insert(ExternalIncludeDirs, externalDirectoryPath .. "/Catch2/include")



function ExternalLibs(Name, IsStaticLib, IncludeDirectory)
	print("External lib : " .. Name)

	group("Externals")
	project(Name)

	language("C++")
	cppdialect("C++17")

	staticruntime("Off")

	if IsStaticLib ~= nil then
		if IsStaticLib then
			kind("StaticLib")
		else
			kind("SharedLib")
		end
	end

	targetdir(rootPath .. "/output/bin/" .. outputDirSementic)
	objdir(rootPath .. "/output/obj/" .. outputDirSementic)

	location(projectsFilesLocation)

	local ThisLibFullExternalIncludeDir = externalDirectoryPath .. "/" .. IncludeDirectory;

	table.insert(ExternalIncludeDirs, ThisLibFullExternalIncludeDir)
	includedirs {ThisLibFullExternalIncludeDir}

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

--------------------------------------------------------------
----------------------- External libs ------------------------
--------------------------------------------------------------


ExternalLibs("Box2D", true, "/Box2D/include")
	files
	{
		externalDirectoryPath .. "/Box2D/src/**.cpp",
		externalDirectoryPath .. "/Box2D/include/**.h",
	}

	includedirs
	{
		externalDirectoryPath .. "/Box2D/src/"
	}

ExternalLibs("fmt", true, "/fmt/include")
	files
	{
		externalDirectoryPath .. "/fmt/src/**.cc",
		externalDirectoryPath .. "/fmt/include/**.h",
	}

ExternalLibs("optick", true, "/optick/src")
	files
	{
		externalDirectoryPath .. "/optick/src/**.cpp",
		externalDirectoryPath .. "/optick/src/**.h",
	}

	defines
	{
		"OPTICK_ENABLE_GPU_VULKAN=0",
		"OPTICK_ENABLE_GPU_D3D12=0",
		"OPTICK_ENABLE_GPU=0",
		"_SILENCE_ALL_CXX17_DEPRECATION_WARNINGS",
		"_CRT_SECURE_NO_WARNINGS",
	}

