outputDirSementic = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}/%{prj.name}"

rootPath = "%{wks.location}/../../../"
enginePath = rootPath .. "engine/"
externalPath = rootPath .. "external/"
projectsFilesLocation = "./projects/" .. _ACTION

print ( "RootPath : " .. rootPath )

workspace "RedEngine"
	startproject "Pong"
	buildmessage ("message")

	configurations
	{
		"Debug",
		"Release"
	}

	platforms 
	{
		"Win64", 
		"Linux64"
	}

	flags
	{
		"MultiProcessorCompile",
	}

	filter { "platforms:Win64" }
		system "windows"
		architecture "x64"

	filter { "platforms:Linux64" }
		system "linux"
		architecture "x64"
	filter {}

	location(projectsFilesLocation);


include "External.lua"
include "RedEngineLib.lua"
include "Templates.lua"
include "Tests.lua"
