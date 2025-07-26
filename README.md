# Robot in Knossos Maze

A C++ console-based maze game inspired by the Greek myth of Theseus and the Minotaur. Navigate a procedurally generated labyrinth, collect powerful items, and escape before the Minotaur catches you!

## � Table of Contents

- [📖 Overview](#-overview)
- [🎮 Game Features](#-game-features)
  - [Core Gameplay](#core-gameplay)
  - [Power-Up Items](#power-up-items)
  - [Game Mechanics](#game-mechanics)
- [🏗️ Architecture](#️-architecture)
  - [Core Classes](#core-classes)
  - [Design Patterns](#design-patterns)
- [🚀 Getting Started](#-getting-started)
  - [Prerequisites](#prerequisites)
  - [Building the Project](#building-the-project)
  - [Running from Command Line](#running-from-command-line)
- [🎯 How to Play](#-how-to-play)
  - [Setup](#setup)
  - [Controls](#controls)
  - [Game Symbols](#game-symbols)
  - [Winning Conditions](#winning-conditions)
- [📁 Project Structure](#-project-structure)
- [🔧 Configuration](#-configuration)
  - [Game Constants](#game-constants-constsh)
  - [Build Configurations](#build-configurations)
- [🧪 Technical Implementation](#-technical-implementation)
  - [Maze Generation Algorithm](#maze-generation-algorithm)
- [📚 Learning Objectives](#-learning-objectives)
- [📄 License](#-license)
- [🏛️ About the Myth](#️-about-the-myth)

## 📖� Overview

The Robot in Knossos Maze is an object-oriented C++ implementation of a classic maze escape game. Players control a robot that must navigate through a dynamically generated maze, collect strategic items, and reach the exit while avoiding the deadly Minotaur that roams the labyrinth.

## 🎮 Game Features

### Core Gameplay

- **Procedural Maze Generation**: Each game features a uniquely generated maze using advanced algorithms
- **Strategic Item Collection**: Find and use powerful items with temporary effects
- **Minotaur**: The Minotaur can attack the robot and limit the maze exploration
- **Multiple Difficulty Levels**: Customize maze size and item count for varied challenges

### Power-Up Items

- **⚔️ Sword**: Allows the robot to slay the Minotaur when encountered
- **🛡️ Shield**: Provides protection from Minotaur attacks
- **🔨 Hammer**: Enables breaking through walls to create new paths
- **🌫️ War Fog**: Reduces vision to a small radius around the robot

### Game Mechanics

- **Turn-based Movement**: Move in four directions (W/A/S/D)
- **Timed Power-ups**: Items have limited duration for strategic usage
- **Dynamic Victory Conditions**: Reach the exit to win, or defeat the Minotaur with the sword
- **Save/Load System**: Continue your progress across game sessions

## 🏗️ Architecture

The project follows object-oriented design principles with clear separation of concerns:

### Core Classes

- **`Game`**: Main game controller managing state and game loop
- **`Maze`**: Represents the maze structure and field matrix
- **`Field`**: Base class for all maze elements (walls, spaces, entities)
- **`Item`**: Abstract base class for collectible power-ups
- **`GameIO`**: Handles all input/output operations and user interface
- **`MazeGenerator`**: Responsible for procedural maze creation

### Design Patterns

- **Inheritance**: Item hierarchy with specialized behaviors
- **Polymorphism**: Dynamic item creation and field management
- **Encapsulation**: Clear public/private interface boundaries
- **Factory Pattern**: Random item generation system

## 🚀 Getting Started

### Prerequisites

- **Visual Studio 2022** (v143 platform toolset)
- **Windows 10/11** (x64 architecture)
- **C++17** or later standard support

### Building the Project

1. **Clone the repository**:

   ```bash
   git clone https://github.com/Vukotije/robot-in-knossos-maze.git
   cd robot-in-knossos-maze
   ```

2. **Open in Visual Studio**:

   - Open `RobotInKnossosMaze.sln` in Visual Studio 2022
   - Select your preferred configuration (Debug/Release)
   - Choose platform (x64 recommended)

3. **Build and run**:
   - Press `F5` to build and run with debugging
   - Or press `Ctrl+F5` to run without debugging
   - Alternatively, use Build → Build Solution (`Ctrl+Shift+B`)

### Running from Command Line

Navigate to the output directory and run:

```bash
# For Debug build
.\x64\Debug\RobotInKnossosMaze.exe

# For Release build
.\x64\Release\RobotInKnossosMaze.exe
```

## 🎯 How to Play

### Setup

1. **Launch the game** and follow the welcome prompts
2. **Choose maze dimensions** (15x15 to 170x170)
3. **Select item count** (3 to 5% of available spaces)
4. **Wait for maze generation** (timing displayed)

### Controls

- **W**: Move up
- **A**: Move left
- **S**: Move down
- **D**: Move right
- **Q**: Quit game at any prompt

### Game Symbols

- **`R`**: Robot (player)
- **`M`**: Minotaur (enemy)
- **`U`**: Entrance
- **`I`**: Exit
- **`#`**: Wall
- **` `**: Empty space
- **`P`**: Random item

### Winning Conditions

- **Primary**: Reach the exit (`I`) safely
- **Alternative**: Defeat the Minotaur with the sword and then reach the exit

## 📁 Project Structure

```
RobotInKnossosMaze/
├── RobotInKnossosMaze/          # Source code directory
│   ├── main.cpp                 # Application entry point
│   ├── Game.{h,cpp}             # Main game controller
│   ├── Maze.{h,cpp}             # Maze structure and management
│   ├── Field.{h,cpp}            # Base class for maze elements
│   ├── Item.{h,cpp}             # Item system and power-ups
│   ├── GameIO.{h,cpp}           # Input/output handling
│   ├── MazeGenerator.{h,cpp}    # Procedural maze generation
│   ├── Consts.h                 # Game constants
│   └── last_maze_state.txt      # Save game state file
├── x64/                         # Build output directory
│   ├── Debug/                   # Debug build artifacts
│   └── Release/                 # Release build artifacts
├── RobotInKnossosMaze.sln       # Visual Studio solution file
└── README.md                    # This file
```

## 🔧 Configuration

### Game Constants (Consts.h)

- **Maze Size**: 15x15 minimum, 170x170 maximum
- **Item Limits**: 3 minimum, 5% of empty spaces maximum
- **War Fog Range**: 3 tiles radius
- **Minotaur Placement**: Upper portion of maze for balanced difficulty

### Build Configurations

- **Debug**: Full debugging symbols, optimizations disabled
- **Release**: Performance optimized, minimal debug info
- **Platform**: x64 (recommended) and x86 support

## 🧪 Technical Implementation

### Maze Generation Algorithm

The maze uses a sophisticated generation algorithm that ensures:

- **Guaranteed Solution**: Always provides a path from entrance to exit
- **Balanced Difficulty**: Strategic placement of walls and open spaces
- **Performance Optimized**: Efficient generation even for large mazes

## 📚 Learning Objectives

This project demonstrates mastery of:

- **Object-Oriented Design**: Inheritance, polymorphism, encapsulation
- **C++ Best Practices**: Modern C++ features, RAII, const-correctness
- **Algorithm Implementation**: Maze generation, pathfinding
- **Software Architecture**: Clean code, modular design, separation of concerns
- **Game Development**: Game loops, state management, user interaction

## 📄 License

This project is developed for educational purposes as part of university coursework in Object-Oriented Programming 2.

## 🏛️ About the Myth

The game draws inspiration from the ancient Greek myth of Theseus and the Minotaur. In the original story, Theseus volunteers to enter the labyrinth of Knossos to face the Minotaur and end the tribute of Athenian youth. With the help of Ariadne's thread, he navigates the maze, defeats the monster, and finds his way out.

In our digital interpretation, you play as a robot facing similar challenges in a procedurally generated labyrinth, using strategic items instead of divine assistance to overcome the mythical beast.

---
