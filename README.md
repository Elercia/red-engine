# Red Engine

Welcome to RedEngine my hobby-projet to learn and experiment things around C++ and game developement. This project has no time limit and is only made on my personal time.

## Goals
The main goal of this projet is to learn modern C++ and game engine development. This is my first try at making something around this, so forgive me if this is not an AAA project. My goal here is to make something usable for small 3D games.

### Goal features

**Graphics:**
* Basic rendering system
* GUI

**Physics :**
* Basic physic engine

**Audio :**
* Basic audio engine

**Scripting :**
* Basic scripting engine

**Core :**
* Entity / Component / System
* Configuration files 
* Memory
 * Custom containers (to replace STL)
 * Memory allocators (frame, pool etc.)
* Input / Event handling
* Threading system
* File system resources management
* Math library (vector, matrix, quaternions)

## About the engine

I try to build the engine using modern C++. This mean using some C++17 features but not "over" use them. 

The ECS is built using recommendation from various sources including :
* [GDC Overwatch Gameplay Architecture and Netcode](https://www.youtube.com/watch?v=W3aieHjyNvw)
* [Gamasutra](https://www.gamasutra.com/blogs/TobiasStein/20171122/310172/The_EntityComponentSystem__An_awesome_gamedesign_pattern_in_C_Part_1.php)	

I also tried to stick to data oriented design [(ex)](https://www.youtube.com/watch?v=rX0ItVEVjHc) 

## Building
### Environement
The projet is built with cmake. This is targeting Windows and linux. 

### Compiling
To build the engine :
```bash
cd red-engine
mkdir build
cd build
cmake ..
cmake --build .
```

Some templates are available in the ``templates`` folder. Specify cmake option ``RED_BUILD_TEMPLATES=OFF`` to disable it.

Test are located in the ``test`` folder. Specify cmake option ``RED_ENABLE_TESTING=OFF`` to disable it.

## Dependencies
This project uses Hunter to manage much of its dependencies. 

Hunter libraries :
- [fmt](https://github.com/fmtlib/fmt)
- [SDL2](https://www.libsdl.org/)
- [Catch2](https://github.com/catchorg/Catch2)

Other libraries :
 - [Optick](https://optick.dev/)
 - [Debug break](https://github.com/scottt/debugbreak)