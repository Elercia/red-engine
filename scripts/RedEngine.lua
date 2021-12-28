outputDirSementic = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}/%{prj.name}"

rootPath = "%{wks.location}/../../../"
enginePath = rootPath .. "engine/"
externalPath = rootPath .. "external/"
projectsFilesLocation = "./projects/" .. _ACTION

cppDialect = "C++20"

availablePlatforms={}
if os.istarget("linux") then
	table.insert(availablePlatforms, "Linux64")
elseif os.istarget("windows") then
	table.insert(availablePlatforms, "Win64")
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

	location(projectsFilesLocation);


include "External.lua"
include "RedEngineLib.lua"
include "Templates.lua"
include "Tests.lua"
