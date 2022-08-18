outputDirSementic = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}-" .. _ACTION .. "/%{prj.name}"

rootPath 				= "%{wks.location}/../../../"
enginePath 				= rootPath .. "engine/"
externalPath 			= rootPath .. "external/"
projectsFilesLocation 	= "./projects/" .. os.target() .. "_" .. _ACTION

cppDialect 				= "C++20"

libsToLink 				= {
							"GL3W",
							"SDL2",
							"Box2D",
							"fmt",
							"fmod",
							"fsbank",
							"fmodstudio",
							"optick",
							"STBI",
							"imgui",
						}

availablePlatforms={}

if os.istarget("linux") then
	table.insert(availablePlatforms, "Linux64")
	table.insert(libsToLink, "dl")
elseif os.istarget("windows") then
	table.insert(availablePlatforms, "Win64")
	table.insert(libsToLink, "shell32")
	table.insert(libsToLink, "Advapi32")
end

workspace "RedEngine"
	startproject "Pong"

	configurations
	{
		"Debug",
		"Release"
	}

	platforms 
	{
		availablePlatforms
	}

	flags
	{
		"MultiProcessorCompile",
	}

	defines
	{
		"FMT_EXCEPTIONS=0",
	}

	filter { "platforms:Win64" }
		system "windows"
		architecture "x64"

		defines
		{
			"_CRT_SECURE_NO_WARNINGS"
		}

	filter { "platforms:Linux64" }
		system "linux"
		architecture "x64"
	filter {}

	location(projectsFilesLocation)

	filter { "toolset:msc" }
  		buildoptions { "/Zc:hiddenFriend-" } -- Bug in MSVC : https://github.com/catchorg/Catch2/issues/2174
	filter {}

	filter { "toolset:clang" }
		buildoptions 
		{ 
			"-Wno-c++98-compat",
			"-Wno-c++98-compat-pedantic"
		} 
	filter {}


include "External.lua"
include "RedEngineLib.lua"
include "Templates.lua"
include "Tests.lua"
