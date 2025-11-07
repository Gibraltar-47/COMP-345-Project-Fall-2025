//
// Created by Howard on 2025-11-03.
//

#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include <iostream>
#include <string>
#include <vector>
#include "../Player/Player.h"
#include "../part1-map/Map.h"

using std::string;
using std::cout;
using std::endl;
using std::cin;



class GameEngine {
    private:
        string state;   //state of the engine
        vector<Player*> players;
        bool gameOver;
        Map* map;
        Deck* deck;

    public:
        GameEngine(); //Default constructor
        GameEngine(const GameEngine& other);
        GameEngine &operator=(const GameEngine &other);
        ~GameEngine();

        void setState(string& state);
        string getState() const;
        void changeState(const string& newState, const string& message);

        void runGame();
        friend ostream& operator<<(ostream& out, const GameEngine& engine);

        void mainGameLoop();
        void reinforcementPhase();
        void issueOrdersPhase(vector<Player*>& allPlayers , Map* map);
        void executeOrdersPhase();

        bool checkWinCondition(const std::vector<Player*>& players, Map* map);
        void waitForUser();

        void addPlayer(Player* player);
        void removePlayer(Player* player);
        void addMap(Map* map);
        void giveDeck(Deck* deck);
        void printAllPlayerOrders(const std::vector<Player*>& players);
};


#endif //COMP_345_PROJECT_FALL_2025_PART2_GAMEENGINE_H