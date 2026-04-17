# 12 Beads Game - C++ SFML

A classic two-player strategy board game where players take turns removing 1-3 beads from a pile of 12. The player who takes the last bead wins! Built with C++ and SFML for smooth graphics and intuitive gameplay.

## Features

- **Two-Player Mode**: Local multiplayer on same device
- **Visual Feedback**: Animated bead removal and turn indicators
- **Score Tracking**: Tracks wins per player
- **Sound Effects**: Satisfying audio feedback for moves and wins
- **Smooth Animations**: SFML-powered transitions

## Game Rules

1. Start with 12 beads in a pile
2. Players alternate turns
3. On each turn, remove 1, 2, or 3 beads
4. Player who takes the LAST bead WINS!

## Controls

- **Mouse**: Click on bead count buttons (1, 2, or 3)
- **Keyboard**: Press 1, 2, or 3 keys
- **R**: Reset game
- **Esc**: Exit

## Technical Details

- **Engine**: SFML 2.5/2.6
- **Language**: C++17
- **Graphics**: 2D sprites and shapes
- **Audio**: SFML Audio module
- **Resolution**: 800x600 (scalable)

## Building

### Prerequisites
- SFML installed and configured
- CMake 3.10+ or direct compiler

### CMake Build
```bash
mkdir build && cd build
cmake ..
make
./BeadsGame
