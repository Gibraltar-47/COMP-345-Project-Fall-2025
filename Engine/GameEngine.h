//
// Created by Howard on 2025-11-03.
//

#ifndef COMP_345_PROJECT_FALL_2025_PART2_GAMEENGINE_H
#define COMP_345_PROJECT_FALL_2025_PART2_GAMEENGINE_H

#include <iostream>
#include <string>
#include <vector>
#include "./Player/Player.h"
#include "./part1-map/Map.h"

using std::string;
using std::cout;
using std::endl;
using std::cin;



class GameEngine {
    private:
        string state;   //state of the engine
        //vector<Player*> players;
        bool gameOver;
        //Map* map;

    public:
        GameEngine(); //Default constructor
        ~GameEngine();

        //void setState(string& state);
        string getState() const;
        void changeState(const string& newState, const string& message);

        void runGame();

        //void mainGameLoop();
        //void reinforcementPhase();
        //void issueOrdersPhase();
        //void executeOrdersPhase();

        //bool checkWinCondition();
        void waitForUser();

        //void addPlayer(Player* player);
        //void removePlayer(Player* player);
        //void addMap(Map* map);
};


#endif //COMP_345_PROJECT_FALL_2025_PART2_GAMEENGINE_H