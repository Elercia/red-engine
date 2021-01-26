workspace "RedEngine"
	architecture "x64"
	startproject "RedEngineLib"

	configurations
	{
		"Debug",
		"Release"
	}

	flags
	{
		"MultiProcessorCompile"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
rootPath = ".."

print ( "RootPath : " .. rootPath )

include "External"
include "RedEngineLib"
include "Templates"
