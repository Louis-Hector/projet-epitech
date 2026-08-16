# ARCADE

**ARCADE** is a project from the module ***G4 - Object-Oriented Programming***. Arcade is a gaming platform : a program that lets the user choose a game to play and keeps a register of player scores

---

## Content

- [Summary](#summary)
- [Installation](#installation)
- [Project structure](#project-structure)
- [Interface sharing](#interface-sharing)
- [Authors](#authors)

---

## Summary

Arcade is a modular gaming platform written in C++.

The main program (core) allows you to:

- select a game
- select a graphics library
- choose your name
- display scores

Everything works with dynamic libraries (.so) loaded at runtime.

## Installation

---

### 1. Git clone the repository on your PC.

```bash
git clone git@github.com:EpitechPGE2-2025/G-OOP-400-LIL-4-1-arcade-18.git
cd G-OOP-400-LIL-4-1-arcade-18
```

### 2. Compile

```bash
make
```

### 3. Launch Arcade

Remplace *your_choice_display.so* by a .so who is a graphic lib.

```bash
./arcade ./lib/your_choice_display.so
```


---

## Project structure

---

```bash
.
├── assets
│   ├── font
│   │   └── Nasa21.ttf
│   ├── minesweeper
│   │   ├── ascii
│   │   │   ├── interrogation.txt
│   │   │   ├── Tile1.txt
│   │   │   ├── Tile2.txt
│   │   │   ├── Tile3.txt
│   │   │   ├── Tile4.txt
│   │   │   ├── Tile5.txt
│   │   │   ├── Tile6.txt
│   │   │   ├── Tile7.txt
│   │   │   ├── Tile8.txt
│   │   │   ├── TileEmpty.txt
│   │   │   ├── TileFlag.txt
│   │   │   ├── TileMine.txt
│   │   │   └── TileUnknown.txt
│   │   ├── images
│   │   │   ├── background.png
│   │   │   ├── interrogation.png
│   │   │   ├── Tile1.png
│   │   │   ├── Tile2.png
│   │   │   ├── Tile3.png
│   │   │   ├── Tile4.png
│   │   │   ├── Tile5.png
│   │   │   ├── Tile6.png
│   │   │   ├── Tile7.png
│   │   │   ├── Tile8.png
│   │   │   ├── TileEmpty.png
│   │   │   ├── TileExploded.png
│   │   │   ├── TileFlag.png
│   │   │   ├── TileMine.png
│   │   │   └── TileUnknown.png
│   │   └── sounds
│   │       ├── explosion.mp3
│   │       ├── game_over.mp3
│   │       ├── snake_death.mp3
│   │       └── win.mp3
│   ├── snake
│       ├── ascii
│       │   ├── apple.txt
│       │   ├── body_horizontal.txt
│       │   ├── body_vertical.txt
│       │   ├── golden_apple.txt
│       │   ├── snake_down.txt
│       │   ├── snake_left.txt
│       │   ├── snake_right.txt
│       │   └── snake_up.txt
│       ├── images
│       │   ├── apple.png
│       │   ├── background.png
│       │   ├── body_down_left.png
│       │   ├── body_down_right.png
│       │   ├── body_horizontal.png
│       │   ├── body_up_left.png
│       │   ├── body_up_right.png
│       │   ├── body_vertical.png
│       │   ├── golden_apple.png
│       │   ├── real.png
│       │   ├── snake_down.png
│       │   ├── snake_left.png
│       │   ├── snake_right.png
│       │   ├── snake_up.png
│       │   ├── tail_down.png
│       │   ├── tail_left.png
│       │   └── tail_right.png
│       └── sounds
│           ├── eat.mp3
│           ├── game_over.mp3
│           └── snake_death.mp3
│   └── tetris
│       ├── ascii
│       │   ├── Tile1.txt
│       │   ├── Tile2.txt
│       │   ├── Tile3.txt
│       │   ├── Tile4.txt
│       │   ├── Tile5.txt
│       │   ├── Tile6.txt
│       │   ├── Tile7.txt
│       │   ├── TileEmpty.txt
│       │   └── TileUnknown.txt
│       ├── images
│       │   ├── background.png
│       │   ├── Tile1.png
│       │   ├── Tile2.png
│       │   ├── Tile3.png
│       │   ├── Tile4.png
│       │   ├── Tile5.png
│       │   ├── Tile6.png
│       │   ├── Tile7.png
│       │   ├── TileEmpty.png
│       │   └── TileUnknown.png
│       └── sounds
│           ├── game_over.mp3
│           └── win.mp3
├── doc
├── lib
├── main.cpp
├── Makefile
├── README.md
├── scores
│   ├── arcade_minesweeper_score.txt
│   └── arcade_snake_score.txt
└── src
    ├── Core
    │   ├── Core.cpp
    │   └── Core.hpp
    ├── Encapsulation
    │   ├── Libdl.cpp
    │   └── Libdl.hpp
    ├── Games
    │   ├── Minesweeper
    │   │   ├── Makefile
    │   │   ├── Minesweeper.cpp
    │   │   └── Minesweeper.hpp
    │   ├── Snake
    │   │   ├── Makefile
    │   │   ├── Snake.cpp
    │   │   └── Snake.hpp
    │   └── Tetris
    │       ├── Makefile
    │       ├── Tetris.cpp
    │       └── Tetris.hpp
    ├── Graphical
    │   ├── Ncurses
    │   │   ├── Makefile
    │   │   ├── Ncurses.cpp
    │   │   └── Ncurses.hpp
    │   ├── SDL2
    │   │   ├── Makefile
    │   │   ├── SDL2.cpp
    │   │   └── SDL2.hpp
    │   └── Sfml
    │       ├── Makefile
    │       ├── Sfml.cpp
    │       └── Sfml.hpp
    ├── Interface
    │   ├── ALib.cpp
    │   ├── ALib.hpp
    │   ├── IDisplay.hpp
    │   ├── IGame.hpp
    │   └── ILib.hpp
    └── Parsing
        ├── Parsing.cpp
        └── Parsing.hpp
```

---

## Interface sharing

- [Keryan Pollet-druelle]()
- ### LEADER [Logan Capoen](https://github.com/logan-capoen) with the email logan.capoen@epitech.eu
- [Paul Ammeloot](https://github.com/PaulAMMELOOT)

---


## Author

- [Noam Bouillet](https://github.com/nomaisthere)
- [Louis Hector](https://github.com/MinFlag)

---
