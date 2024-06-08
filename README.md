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
https://github.com/boukeweel/BewGin


##Enemies
The enemies follow paths defined by Bézier curves. I got this idea from a YouTube video about making SDL Galaga, and it seemed like the best and easiest way to implement various enemy paths. Their behaviors are handled by a state machine, which allows for easy switching between different behaviors as needed.

## enemy spawning.
Enemies are created and spawned by the EnemySpawnerComponent class. Once created, they are stored in a variable for reuse, utilizing object pooling. This approach eliminates the need to create new enemies for each new formation or level.

## Player shooting
Similar to enemy spawning, an object pooling system is used to reuse the bullets that are shot by the player.

## Game time
I chose to implement a static game time class to avoid passing delta time in every update function. This way, it can be accessed as needed without redundant parameter passing.

## sounds loading
The sound system requires sounds to be preloaded due to the small scale of the project. In the future, I plan to implement sound loading via a separate thread to prevent long initial load times.

## sounds playing
Audio playback is handled on a separate thread with an event queue, ensuring it does not pause the main game.

## input
In the input system, you can assign specific actions to keys on the keyboard or buttons on the controller. This allows for easy customization and modification of control schemes. Users have the freedom to choose which keys or buttons are mapped to each action, making it simple to change or expand the control setup as needed.
