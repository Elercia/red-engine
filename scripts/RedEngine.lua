outputDirSementic = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

rootPath = "../"
enginePath = rootPath .. "engine/"
externalPath = rootPath .. "external/"
projectLocation = "./projects/"

print ( "RootPath : " .. rootPath )

workspace "RedEngine"
	startproject "RedEngineLib"

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
		system "Windows"
		architecture "x64"

	filter { "platforms:Linux64" }
		system "Linux"
		architecture "x64"
	filter ""

	location(projectLocation);


include "External.lua"
include "RedEngineLib.lua"
include "Templates.lua"
