# Chess

This repository hosts a C++ implementation of a GUI chess game featuring a terminal menu for game mode selection.

---
## Features

* Choose from multiple game modes:
  1) **Two Players**: Play against another player on the same computer.
  2) **Player vs AI**: Challenge one of three AI difficulty levels.

* Menu options include:
  * **Game Type Selection**: Easily switch between two-player mode and single-player mode against AI.
  * **Color Selection**: Choose your preferred color as either white or black for player-controlled pieces.
  * **Save Game**: Save your current game progress for later continuation.
  * **Load Games**: Load previously saved games to resume where you left off.
  * **Tutorial**: Access a tutorial to learn or the rules of chess.

---
## Types of oponents

The opponents vary in difficulty:
  1) **Easy**: Implements random movements to simulate a novice player.
  2) **Medium**: Takes advantage of opportunities to capture pieces when possible.
  3) **Hard**: Utilizes advanced algorithms - alpha-beta pruning to make optimal moves, providing a formidable opponent.

## Controls

 * **Z**: Undo the last move during gameplay.
 * **S**: Save the current game progress.

---
## Prerequisites:

Ensure you have the following libraries installed for proper graphics rendering and image handling

* **SDL2**
`apt install libsdl2-dev`

* **SDL2 image**
`apt install libsdl2-image-dev`

---
## Known issues

* **Basic Makefile**: The current Makefile compiles all files simultaneously, resulting in longer compilation times.
* **SDL Memory Leaks**
