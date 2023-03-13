![Project build status](https://github.com/Elercia/red-engine/workflows/CI%20Workflow/badge.svg?branch=develop)
# Red Engine

Welcome to RedEngine my hobby-project to learn and experiment things around C++ and game development. This project has no time limit and is only made on my personal time.

## Goals
The main goal of this project is to experiment around modern C++ and game engine development. I want to make this usable as a 2D Game engine for simple games. 

### Goal features

**Rendering :**
* Basic rendering system built around OpenGL (to keep it simple)
* Widgets for menus and in game UI

**Physics :**
* Physics engine (with rigid bodies, forces, contacts, triggers) all wrapped around Box2D

**Audio :**
* Audio engine using FMod (with event triggers and direct launch)

**Scripting :**
* Fully scriptable gameplay using language like [Lua](https://www.lua.org/) or [ChaiScript](https://chaiscript.com/) (tbd)

**Core :**
* Entity / Component / System
* Configuration management using CVars
* Memory
 * Custom containers to replace STL (Array, Strings)
 * Memory allocators (frame buffer, pool allocator ...)
* Input / Event handling for mouse / keyboard and gamepads
* Multi threading system using thread pool and dispatcher
* Resources management
* Math library (vector and other basics math for 2D games)

## About the engine

Hierarchy :
- ``engine`` The engine sources (divided into includes and sources)
    - ``Audio`` Audio system of the engine. Including audio related components, resources and system.
    - ``Core`` Include the ECS base, configuration system, containers, memory management and debug utilities. All the required things used by all the engine modules.
    - ``Filesystem`` Path, File wrappers. 
    - ``Input`` User input handling. From registering raw inputs and creating gameplay events.
    - ``Level`` Level (Scenes) code. 
    - ``Math`` Some people say its mandatory. 
    - ``Physics`` Physics system of the engine. Including physics related components, resources and system.
    - ``Rendering`` Rendering system of the engine. Including rendering related components, resources and system.
    - ``Resources`` Base classes and systems used to load and manage systems.
    - ``Thread`` Thread scheduler and Thread utilities.
    - ``Utils`` Everything that don't go inside other categories.
- ``external`` External library (using Git sub modules or downloaded from there repositories)
- ``scripts`` Useful scripts such as generating project
- ``templates`` Projects game templates (used to show off engine working) 
- ``test`` Unit / functional tests

## Building
### Development environment

This is targeting Windows and Linux and is using [Premake](https://github.com/premake/premake-core) as a build configuration tool.
You can generate all projects files that provides premake (cf premake documentation).

We provide utility scripts to generate common IDE / Editor project files such as Make / VS 2019. 
Simply use the ``GenerateXXXProject.sh/bat`` inside the ``scripts`` folder.
Project files are generated in ``scripts/projects`` folder.

### Linux build

You will need to install SDL2 development build on you distrib by running a command like ``sudo apt install libsdl2-dev``.

## Dependencies
The engine uses the following dependencies :
- [Catch2](https://github.com/catchorg/Catch2) as the test framework.
- [Box2D](https://github.com/erincatto/box2d) for engine physics simulation.
- [Debug break](https://github.com/scottt/debugbreak) as a portable debugger breaking tool.
- [FMOD](https://www.fmod.com/) for audio processing.
- [fmt](https://github.com/fmtlib/fmt) as the string formatting used in the logger.
- [Nlohmann JSON](https://github.com/nlohmann/json) for loading all the resource (saved in JSON format).
- [Optick](https://optick.dev/) to register profiling events.
- [SDL2](https://www.libsdl.org/) to manage platform dependent code such as input handling and window creation.
- [STB (image related)](https://github.com/nothings/stb) to load / write images on CPU side.
- [GL3W](https://github.com/skaslev/gl3w) to load OpenGL functions.  
- [Dear ImGui](https://github.com/ocornut/imgui) to display debug / utils.
- [GLM](https://github.com/g-truc/glm) just to make sure the math are correct (just in case)
- [Marl](https://github.com/google/marl) to manage Threads & Fibers.
