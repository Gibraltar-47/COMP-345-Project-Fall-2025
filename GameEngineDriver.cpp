//
// Created by abede on 2025-10-04.
//

#include "GameEngine.h"
#include "GameEngineDriver.h"



void testGameStates() {
    GameEngine game;
    std::cout << "PRINTING GAME ENGINE WITH STREAM INSERTION: "<< std::endl << game << std::endl;
    game.play();

}
