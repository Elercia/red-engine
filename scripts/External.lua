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

filter { "platforms:Win64" }
	postbuildcommands { "{COPY} ../../../external/Fmod/core/lib/x64/fmod.dll %{cfg.buildtarget.directory}" }
	postbuildcommands { "{COPY} ../../../external/Fmod/fsbank/lib/x64/fsbank.dll %{cfg.buildtarget.directory}" }
	postbuildcommands { "{COPY} ../../../external/Fmod/fsbank/lib/x64/libfsbvorbis64.dll %{cfg.buildtarget.directory}" }
	postbuildcommands { "{COPY} ../../../external/Fmod/fsbank/lib/x64/opus.dll %{cfg.buildtarget.directory}" }
	postbuildcommands { "{COPY} ../../../external/Fmod/studio/lib/x64/fmodstudio.dll %{cfg.buildtarget.directory}" }
filter {}

-- Json
table.insert(ExternalIncludeDirs, externalDirectoryPath .. "/nlohmann_json/single_include")

-- Catch2
table.insert(ExternalIncludeDirs, externalDirectoryPath .. "/Catch2/include")



function ExternalLibs(Name, IsStaticLib, IncludeDirectory)
	print("External lib : " .. Name)

	group("Externals")
	project(Name)

	language("C++")
	cppdialect(cppDialect)

	staticruntime("Off")
	editandcontinue("Off")

	warnings("Off")

	if enableExceptions then
		exceptionhandling("On")
	else
		exceptionhandling("Off")
	end

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

	filter { "configurations:Debug" }
		defines 
		{
			"RED_DEBUG", 
			"RED_DEVBUILD", 
			"RED_BREAK_ON_ASSERT",
			"RED_USE_PROFILER" 
		}

		runtime "Debug"
		symbols "Full"
	filter {}

	filter { "configurations:ReleaseWithDebugInfo" }
		defines 
		{
			"RED_DEBUG_RELEASE",
			"RED_DEVBUILD",
			"RED_USE_PROFILER"
		}

		runtime "Release"
		optimize "on"
		symbols "Full"
	filter {}

	filter { "configurations:Release" }
		defines "RED_RELEASE"
		runtime "Release"
		optimize "on"
		symbols "Off"
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

	defines
	{
		"FMT_EXCEPTIONS=0"
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
	}

ExternalLibs("GL3W", true, "/gl3w/include")
	files
	{
		externalDirectoryPath .. "/gl3w/src/**.c",
		externalDirectoryPath .. "/gl3w/include/**.h",
	}

	includedirs
	{
		externalDirectoryPath .. "/gl3w/include/"
	}

ExternalLibs("STBI", true, "/stbi/include")
	files
	{
		externalDirectoryPath .. "/stbi/src/**.c",
		externalDirectoryPath .. "/stbi/include/**.h",
	}

	includedirs
	{
		externalDirectoryPath .. "/stbi/include/"
	}

ExternalLibs("ImGui", true, "/imgui/")
	files
	{
		externalDirectoryPath .. "/imgui/backends/imgui_impl_sdl2.cpp",
		externalDirectoryPath .. "/imgui/backends/imgui_impl_opengl3.cpp",
		externalDirectoryPath .. "/imgui/imgui*.cpp",
	}

	includedirs
	{
		externalDirectoryPath .. "/imgui/",
		externalDirectoryPath .. "/imgui/backends/",
		externalDirectoryPath .. "/SDL2/include/SDL2/",
		externalDirectoryPath .. "/SDL2/include/",
	}

	table.insert(ExternalIncludeDirs, externalDirectoryPath .. "/imgui/")
	table.insert(ExternalIncludeDirs, externalDirectoryPath .. "/imgui/backends/")

ExternalLibs("glm", true, "/glm/include")
	files
	{
		externalDirectoryPath .. "/glm/glm/**.h",
		externalDirectoryPath .. "/glm/glm/**.c",
		externalDirectoryPath .. "/glm/glm/**.hpp",
		externalDirectoryPath .. "/glm/glm/**.cpp",
	}

	includedirs
	{
		externalDirectoryPath .. "/glm"
	}

	table.insert(ExternalIncludeDirs, externalDirectoryPath .. "/glm/")

ExternalLibs("marl", true, "/marl/include")
	local marlSourcePath = externalDirectoryPath .. "/marl"

	files
	{
		marlSourcePath .. "/src/debug.cpp",
		marlSourcePath .. "/src/memory.cpp",
		marlSourcePath .. "/src/scheduler.cpp",
		marlSourcePath .. "/src/thread.cpp",
		marlSourcePath .. "/src/trace.cpp",
	}
	
	filter { "platforms:Linux64" }
		files
		{
			marlSourcePath .. "/src/osfiber_aarch64.c",
			marlSourcePath .. "/src/osfiber_arm.c",
			marlSourcePath .. "/src/osfiber_asm_aarch64.S",
			marlSourcePath .. "/src/osfiber_asm_arm.S",
			marlSourcePath .. "/src/osfiber_asm_loongarch64.S",
			marlSourcePath .. "/src/osfiber_asm_mips64.S",
			marlSourcePath .. "/src/osfiber_asm_ppc64.S",
			marlSourcePath .. "/src/osfiber_asm_rv64.S",
			marlSourcePath .. "/src/osfiber_asm_x64.S",
			marlSourcePath .. "/src/osfiber_asm_x86.S",
			marlSourcePath .. "/src/osfiber_loongarch64.c",
			marlSourcePath .. "/src/osfiber_mips64.c",
			marlSourcePath .. "/src/osfiber_ppc64.c",
			marlSourcePath .. "/src/osfiber_rv64.c",
			marlSourcePath .. "/src/osfiber_x64.c",
			marlSourcePath .. "/src/osfiber_x86.c",
		}
	filter {}


	includedirs
	{
		marlSourcePath .. "/include/"
	}

	table.insert(ExternalIncludeDirs, marlSourcePath .. "/include/")
