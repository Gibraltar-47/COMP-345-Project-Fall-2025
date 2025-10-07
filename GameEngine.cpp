//
// Created by abede on 2025-09-28.
//

#include <iostream>
#include <string>
#include "GameEngine.h"






    GameEngine::GameEngine() = default;


   void GameEngine::loadMap() {
        gameState = "map loaded";
        std::cout << "Map loaded... " << std::endl;

        std::cout << "Valid commands: loadmap/validatemap" << std::endl;

        std::cin >> input;

        while(input != "loadmap" && input!= "validatemap"){
        std::cout << "Invalid command entered" << std::endl;
        std::cout << "Valid commands: loadmap/validatemap" << std::endl;
        std::cin >> input;
}
        if(input == "loadmap"){
        loadMap();
    }

}



   void GameEngine::validateMap() {
        gameState = "map validated";
        std::cout << "Map validated" << std::endl;
        std::cout << "Valid commands: addplayer" << std::endl;
        std::cin >> input;

        while(input != "addplayer"){
            std::cout << "Invalid command entered" << std::endl;
            std::cout << "Valid commands: addplayer" << std::endl;
            std::cin >> input;
            }
       //verify input if correct and call addPlayer()
    }


   void GameEngine::addPlayer() {
    gameState = "players added";
    std::cout << "Players added" << std::endl;
       std::cout << "Valid commands: addplayer/assigncountries" << std::endl;

        std::cin >> input;

        while(input != "addplayer" && input != "assigncountries"){
            std::cout << "Invalid command entered" << std::endl;
            std::cout << "Valid commands: addplayer/assigncountries" << std::endl;
            std::cin >> input;
        }
        if(input == "addplayer"){
           addPlayer();
        }


}

   void GameEngine::loopEntrance() {
        gameState = "assign reinforcement";
       std::cout << "Valid commands: issueorder" << std::endl;
        std::cin >> input;

        while(input != "issueorder"){
            std::cout << "Invalid command entered" << std::endl;
            std::cout << "Valid commands: issueorder" << std::endl;
            std::cin >> input;
        }
        if(input == "issueorder"){
            issueOrder();
        }
}

   void GameEngine::assignCountries() {
    gameState = "assign reinforcement";
    std::cout << "Countries assigned" << std::endl;

    loopEntrance();


}

  void  GameEngine::issueOrder() {
    gameState = "issue orders";
    std::cout << "Order issued" << std::endl;
       std::cout << "Valid commands: issueorder/endissueorders" << std::endl;
    std::cin >> input;

        while(input != "issueorder" && input != "endissueorders"){
            std::cout << "Invalid command entered" << std::endl;
            std::cout << "Valid commands: issueorder/endissueorders" << std::endl;
            std::cin >> input;
        }

    if(input == "issueorder"){
    issueOrder();
    }

    if(input == "endissueorders"){
    endIssueOrders();
    }

}

   void GameEngine::endIssueOrders() {
    gameState = "execute orders";
    std::cout << "Order phase ended" << std::endl;
       std::cout << "Valid commands: execorder/endexecorders/win" << std::endl;
        std::cin >> input;

        while(input != "execorder" && input != "endexecorders" && input != "win"){
            std::cout << "Invalid command entered" << std::endl;
            std::cout << "Valid commands: execorder/endexecorders/win" << std::endl;
            std::cin >> input;
        }

        if(input == "execorder"){
            execOrder();

        }

        if(input == "endexecorders"){
            endExecOrders();
        }

        if(input == "win"){
            win();
        }

}

   void GameEngine::execOrder() {
    gameState = "execute orders";
    std::cout << "Order executed" << std::endl;
       std::cout << "Valid commands: execorder/endexecorders/win" << std::endl;
        std::cin >> input;

        while(input != "execorder" && input != "endexecorders" && input != "win"){
            std::cout << "Invalid command entered" << std::endl;
            std::cout << "Valid commands: execorder/endexecorders/win" << std::endl;
            std::cin >> input;
        }

        if(input == "execorder"){
            execOrder();

        }

        if(input == "endexecorders"){
            endExecOrders();
        }

        if(input == "win"){
            win();
        }

}

   void GameEngine::endExecOrders() {
    gameState = "assign reinforcement";
    std::cout << "Order phase ended" << std::endl;
    loopEntrance();

}

   void GameEngine::win() {
    gameState = "win";
    std::cout << "Victory" << std::endl;
       std::cout << "Valid commands: play/end" << std::endl;
    std::cin >> input;
    while(input != "play" && input != "end"){
        std::cout << "Invalid command entered" << std::endl;
        std::cout << "Valid commands: play/end" << std::endl;
        std::cin >> input;
    }


    if(input == "end"){
        end();
    }

}

   void GameEngine::play() {
    gameState = "play";
    std::cout << "Game starting..." << std::endl;
    std::cout << "Valid commands: loadmap" << std::endl;
    std::cin >> input;
       while (input != "loadmap") {
           std::cout << "Invalid command entered" << std::endl;
           std::cout << "Valid commands: loadmap" << std::endl;
           std::cin >> input;
       }

    }

    void GameEngine::end(){

    gameState = "end";
    std::cout << "Game ended" << std::endl;

}

    std::string GameEngine::getGameState() {
    return gameState;
    }








