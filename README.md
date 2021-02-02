![Project build status](https://github.com/Elercia/red-engine/workflows/CI%20Workflow/badge.svg?branch=master)
# Red Engine

Welcome to RedEngine my hobby-projet to learn and experiment things around C++ and game developement. This project has no time limit and is only made on my personal time.

## Goals
The main goal of this projet is to learn modern C++ and game engine development. This is my first try at making something around this. My goal here is to make something usable for small 3D games.

### Goal features

**Rendering :**
* Basic rendering system built around Vulkan (tbd.)
* Widgets and InGame GUI

**Physics :**
* Basic physic engine (forces, contacts, triggers)

**Audio :**
* Basic audio engine using Fmod (with event triggers and direct launch)

**Scripting :**
* Basic scripting engine using regular C++ and Lua 

**Core :**
* Entity / Component / System
* Configuration files & Cvar management to dispatch the confiuration around all components
* Memory
 * Custom containers to replace STL (Array)
 * Memory allocators (frame buffer, pool allocator ...)
* Input / Event handling for mouse / keyboard and gamepads
* Multi threading system using thread pool and dispatcher
* Resources management
* Math library (vector and other basics math for 2D games)

## About the engine

I try to build the engine using modern C++. This mean using some C++17 features but not "over" use them. 

The ECS is built using recommendation from various sources including :

* [GDC Overwatch Gameplay Architecture and Netcode](https://www.youtube.com/watch?v=W3aieHjyNvw)
* [Gamasutra](https://www.gamasutra.com/blogs/TobiasStein/20171122/310172/The_EntityComponentSystem__An_awesome_gamedesign_pattern_in_C_Part_1.php)	

I also tried to stick to [data oriented design](https://www.youtube.com/watch?v=rX0ItVEVjHc) as much as possible. 

## Building
### Environement

The project uses [Premake](https://github.com/premake/premake-core) as a build configuration file.
This is targeting Windows and Cmake 

To generate the project run the script ``GenerateProject`` located in the ``scripts`` folder.

## Dependencies
The engine uses the following dependencies :

- [Box2D](https://github.com/erincatto/box2d)
- [Catch2](https://github.com/catchorg/Catch2)
- [Debug break](https://github.com/scottt/debugbreak)
- [FMOD](https://www.fmod.com/)
- [fmt](https://github.com/fmtlib/fmt)
- [Nlohmann JSON](https://github.com/nlohmann/json)
- [Optick](https://optick.dev/)
- [SDL2](https://www.libsdl.org/)
- [SDL Image](https://www.libsdl.org/projects/SDL_image/)
