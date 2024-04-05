# Minigin

Minigin is a very small project using [SDL2](https://www.libsdl.org/) and [glm](https://github.com/g-truc/glm) for 2D c++ game projects. It is in no way a game engine, only a barebone start project where everything sdl related has been set up. It contains glm for vector math, to aleviate the need to write custom vector and matrix classes.

[![Build Status](https://github.com/avadae/minigin/actions/workflows/msbuild.yml/badge.svg)](https://github.com/avadae/msbuild/actions)
[![GitHub Release](https://img.shields.io/github/v/release/avadae/minigin?logo=github&sort=semver)](https://github.com/avadae/minigin/releases/latest)

# Goal

Minigin can/may be used as a start project for the exam assignment in the course 'Programming 4' at DAE. In that assignment students need to recreate a popular 80's arcade game with a game engine they need to program themselves. During the course we discuss several game programming patterns, using the book '[Game Programming Patterns](https://gameprogrammingpatterns.com/)' by Robert Nystrom as reading material. 

# Disclaimer

Minigin is, despite perhaps the suggestion in its name, not a game engine. It is just a very simple sdl2 ready project with some of the scaffolding in place to get started. None of the patterns discussed in the course are used yet (except singleton which use we challenge during the course). It is up to the students to implement their own vision for their engine, apply patterns as they see fit, create their game as efficient as possible.

# Use

Download the latest release of this project and compile/run in visual studio. Since students need to have their work on github too, they can use this repository as a template.



# BewGin Documantation

## Agenda

### API
#### MainFiles
1. [AI](#API)
2. [Mainfiles](#Mainfiles)
3. [main.cpp](#main.cpp)
4. [BewGin.cpp](#BewGin.cpp)
5. [Render.cpp](#Render.cpp)
6. [ResourceManager.cpp](#ResourceManager.cpp)
7. [scene.cpp](#scene.cpp)
8. [sceneManger.cpp](#sceneManger.cpp)
9. [texture.cpp](#texture.cpp)
10. [font.cpp](#font.cpp)
11. [singelton.h](#singelton.h)

#### Input
12. [InputManger.h](#InputManger.h)

# API 

## Mainfiles
### main.cpp
- **main()**: Gets the engine and calls the run function.

- **Load()**: Load all the game objects for the test project in the game engine.

- **SetControllersPlayer1 SetControllersPlayer2**: Set the controls for the players.

- **AddTestingInputs**: Add the inputs to the input map so that it's able to be used.

### BewGin.cpp

- **BewGin()**: Creates the window; here you can set the Width and Height of the window.

- **~BewGin()**: ...

- **Run()**: Starts the game loop for the game; the game loop is now limited to around 60 fps.

- **PrintSDLVersion()**: Prints out all the SDL versions that are being used.


### Render.cpp

### ResourceManager.cpp

### scene.cpp

### sceneManger.cpp

### texture.cpp

### font.cpp

### singelton.h


## Input
### InputManger.h


