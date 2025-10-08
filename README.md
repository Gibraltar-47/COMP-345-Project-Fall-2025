# COMP-335---Project---Fall-2025

## Overview
This project is a modular C++ game engine that simulates strategic gameplay using maps, players, orders, and cards. Each component can be tested individually and extended easily for future development.

## Features
- **Game Engine Core**: Main logic and control flow of the game.
- **Map System**: Manages maps and territories for gameplay.
- **Player System**: Allows players to issue orders and interact in the game.
- **Orders Module**: Supports various types of orders (`Advance`, `Deploy`, etc.).
- **Deck & Cards**: Implements a card system for strategic gameplay.
- **Drivers & Tests**: Each module comes with driver files for testing.

## Project Structure
Project/
├─ Engine/
│   ├─ GameEngine.cpp
│   └─ GameEngineDriver.cpp
├─ Orders/
│   ├─ Orders.cpp
│   └─ OrdersDriver.cpp
├─ Part-4-Deck/
│   ├─ Cards.cpp
│   └─ CardsDriver.cpp
├─ part1-map/
│   ├─ Map.cpp
│   └─ MapDriver.cpp
├─ Player/
│   ├─ Player.cpp
│   ├─ PlayerTest.cpp
│   └─ PlayerDriver.cpp
└─ MainDriver.cpp

## Requirements
- GCC/G++ compiler
- C++11 or higher

## Compilation
Compile the project using:

```
g++ Engine/GameEngine.cpp Engine/GameEngineDriver.cpp \Orders/Orders.cpp Orders/OrdersDriver.cpp \Part-4-Deck/Cards.cpp Part-4-Deck/CardsDriver.cpp \part1-map/Map.cpp part1-map/MapDriver.cpp \Player/PlayerTest.cpp Player/PlayerDriver.cpp \MainDriver.cpp -std=c++11
```
Running the Project
```
After compilation, run the game with:
```
