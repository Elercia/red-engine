-- Include directories relative to root folder (solution directory)
externalDirectoryPath= rootPath .. "/external"

IncludeDir = {}
IncludeDir["DebugBreak"] = externalDirectoryPath .. "/DebugBreak"
IncludeDir["FmodCore"] = externalDirectoryPath .. "/Fmod/core/inc"
IncludeDir["FmodFsBank"] = externalDirectoryPath .. "/Fmod/fsbank/inc"
IncludeDir["FmodStudio"] = externalDirectoryPath .. "/Fmod/studio/inc"
IncludeDir["optick"] = externalDirectoryPath .. "/optick/src"
IncludeDir["SDL2"] = externalDirectoryPath .. "/SDL2/include"
IncludeDir["SDL2_internal"] = externalDirectoryPath .. "/SDL2/include/SDL2"
IncludeDir["SDL_image"] = externalDirectoryPath .. "/SDL_image/include"
IncludeDir["nlohmann_json"] = externalDirectoryPath .. "/nlohmann_json/single_include"
IncludeDir["fmt"] = externalDirectoryPath .. "/fmt/include"
IncludeDir["Box2D"] = externalDirectoryPath .. "/Box2D/include"

group "Externals"
	-- include( "../external/optick" )