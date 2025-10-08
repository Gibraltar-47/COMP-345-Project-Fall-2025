# COMP-335---Project---Fall-2025

## Overview
COMP345

## Features
- **Game Engine**: Main logic and control flow of the game.
- **Map System**: Manages maps and territories for gameplay.
- **Player System**: Allows players to issue orders and interact in the game.
- **Orders Module**: Supports various types of orders.
- **Deck & Cards**: Implements a card system.

## Project Structure
```
Project
├─ Engine
│   ├─ GameEngine.cpp
│   └─ GameEngineDriver.cpp
├─ Orders
│   ├─ Orders.cpp
│   └─ OrdersDriver.cpp
├─ Part-4-Deck
│   ├─ Cards.cpp
│   └─ CardsDriver.cpp
├─ part1-map
│   ├─ Map.cpp
│   ├─ MapDriver.cpp
│   └─ mapFiles/ 
│       ├─ map1.map
│       ├─ map2.map
│       └─ ...
├─ Player
│   ├─ Player.cpp
│   ├─ PlayerTest.cpp
│   └─ PlayerDriver.cpp
└─ MainDriver.cpp
```
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
