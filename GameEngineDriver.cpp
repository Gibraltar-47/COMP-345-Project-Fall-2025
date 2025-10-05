//
// Created by abede on 2025-10-04.
//

#include "GameEngine.h"

#include <iostream>


void testGameStates(){
    GameEngine game;


    while(game.getGameState() != "end"){
        game.play();
        game.loadMap();
        game.validateMap();
        game.addPlayer();
        game.assignCountries();
    }
}






int main(){

testGameStates();

return 0;
}