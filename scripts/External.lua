-- Include directories relative to root folder (solution directory)
externalDirectoryPath= rootPath .. "/external"

IncludeDir = {}
LibDir = {}


IncludeDir["DebugBreak"] = externalDirectoryPath .. "/DebugBreak"
IncludeDir["FmodCore"] = externalDirectoryPath .. "/Fmod/core/inc"
IncludeDir["FmodFsBank"] = externalDirectoryPath .. "/Fmod/fsbank/inc"
IncludeDir["FmodStudio"] = externalDirectoryPath .. "/Fmod/studio/inc"
IncludeDir["optick"] = externalDirectoryPath .. "/optick/src"
IncludeDir["SDL_image"] = externalDirectoryPath .. "/SDL_image/include"
IncludeDir["nlohmann_json"] = externalDirectoryPath .. "/nlohmann_json/single_include"
IncludeDir["fmt"] = externalDirectoryPath .. "/fmt/include"
IncludeDir["Box2D"] = externalDirectoryPath .. "/Box2D/include"

function ExternalLibs(Name, IsStaticLib, IncludeDirectory)
	group("Externals")
	project(Name)

	language("C++")
	cppdialect("C++17")

	if IsStaticLib ~= nil then
		if IsStaticLib then
			kind "StaticLib"
		else
			kind "SharedLib"
		end
	end

	targetdir(rootPath .. "/output/bin/" .. outputDirSementic .. "/%{prj.name}")
	objdir(rootPath .. "/output/obj/" .. outputDirSementic .. "/%{prj.name}")

	IncludeDir[Name] = externalDirectoryPath .. "/" .. IncludeDirectory
end

ExternalLibs("SDL2", nil, "SDL2/include")
	IncludeDir["SDL2_internal"] = externalDirectoryPath .. "/SDL2/include/SDL2"

	kind("StaticLib")

	filter "system:windows"
		kind          "SharedLib"
		staticruntime "off"
	filter {}

	flags {
		"NoRuntimeChecks", -- Only used on Visual Studio.
		"NoBufferSecurityCheck"
	}


