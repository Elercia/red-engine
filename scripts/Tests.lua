group("Tests")

project ("RedEngineTest")
    kind "ConsoleApp"
    language("C++")
    cppdialect("C++17")

    rtti("Off")
    exceptionhandling("Off")
    warnings("Extra")
    flags("NoPCH")
    staticruntime("Off")

    targetdir(rootPath .. "/output/bin/" .. outputDirSementic)
    objdir(rootPath .. "/output/obj/" .. outputDirSementic)

    location(projectsFilesLocation)

    local testPath = rootPath .. "test/"
    files {
        testPath .. "src/**.cpp",
        testPath .. "include/**.hpp",
        externalDirectoryPath .. "/Catch2/src/*.cpp"
    }
    
    includedirs
    {
        enginePath .. "include/",
        testPath .. "include/",
        ExternalIncludeDirs,
    }

    libdirs
    {
        ExternalLibDirs
    }

    links
    {
        "RedEngineLib",
        "SDL2main",
        "SDL2",
        "SDL2_image",
        "Box2D",
        "fmt",
        "fmod",
        "fsbank",
        "fmodstudio",
        "optick",
    }

    filter "configurations:Debug"
        defines "RED_DEBUG"
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        defines "RED_RELEASE"
        runtime "Release"
        optimize "on"

    filter {}