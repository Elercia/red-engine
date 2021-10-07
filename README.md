![Project build status](https://github.com/Elercia/red-engine/workflows/CI%20Workflow/badge.svg?branch=master)
# Red Engine

Welcome to RedEngine my hobby-projet to learn and experiment things around C++ and game developement. This project has no time limit and is only made on my personal time.

## Goals
The main goal of this projet is to experiment around modern C++ and game engine development. I want to make this usable as a 2D Game engine for simple games. 

### Goal features

**Rendering :**
* Basic rendering system built around Opengl (to keep it simple)
* Widgets for menus and in game UI

**Physics :**
* Physics engine (with rigid bodies, forces, contacts, triggers) all wrapped around Box2D

**Audio :**
* Audio engine using Fmod (with event triggers and direct launch)

**Scripting :**
* Fully sciptable gameplay using [Lua](https://www.lua.org/)  

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
    - ``Utils`` Everything that don't go inside other categories.
- ``exernal`` External library (using Git sub modules or downloaded from there repositories)
- ``scripts`` Usefull scripts such as generating project
- ``templates`` Projects game templates (used to show off engine working) 
- ``test`` Unit / fonctional tests

## Building
### Environement

The project uses [Premake](https://github.com/premake/premake-core) as a build configuration file.
This is targeting Windows and Linux

To generate the project run the script ``GenerateProject`` located in the ``scripts`` folder.
Project files are generated in ``scripts/project`` folder.

## Dependencies
The engine uses the following dependencies :
- [Catch2](https://github.com/catchorg/Catch2) as the test framework.
- [Box2D](https://github.com/erincatto/box2d) for engine physics simulation.
- [Debug break](https://github.com/scottt/debugbreak) as a portable debugguer breaking tool.
- [FMOD](https://www.fmod.com/) for audio processing.
- [fmt](https://github.com/fmtlib/fmt) as the string formating used in the logger.
- [Nlohmann JSON](https://github.com/nlohmann/json) for loading all the resource (saved in json format).
- [Optick](https://optick.dev/) to register profiling events.
- [SDL2](https://www.libsdl.org/) to manage platform dependent code such as input handling and window creation.
- [STB (image related)](https://github.com/nothings/stb) to load / write images on CPU side.
- [GL3W](https://github.com/skaslev/gl3w) to load OpenGL functions.  

