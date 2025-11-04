//
// Created by Howard on 2025-11-03.
//
#include "GameEngine.h"
#include <iostream>
#include <limits>

using std::string;
using std::cout;
using std::endl;
using std::cin;

GameEngine::GameEngine() : state("start"), gameOver(false) {}
GameEngine::~GameEngine() = default;

string GameEngine::getState() const {
    return state;
}
void GameEngine::changeState(const string& newState, const string& message) {
    state = newState;
    cout << message << endl;
    cout << "Now in state: " << state << endl;
}

void GameEngine::runGame() {
    cout << "Welcome to the Game Engine!" << endl << endl;
    cout << "---------------------" << endl;
    string command;
    state = "start";
    gameOver = false;

    while (!gameOver) {
        cout << "Current State: " << getState() << endl;
        cout << "Enter a command: (type 'loadmap' to proceed)";
        cin >> command;

        if (command == "exit") { //quick exit
            gameOver = true;
        }
        else if (command == "loadmap" && (state == "start" || state == "maploaded")) {
            changeState("maploaded", "Map loaded.(type 'validatemap' to proceed)");
        }
        else if (command == "validatemap" && state == "maploaded") {
            changeState("mapvalidated", "Map validated.(type 'addplayer' to proceed)");
        }
        else if (command == "addplayer" && (state == "mapvalidated" || state == "playersadded")) {
            changeState("playersadded", "Players added.(type 'assigncountries' to proceed)");
        }
        else if (command == "assigncountries" && state == "playersadded") {
            changeState("maingameloop", "Game loop has begun(type 'win' to proceed)");
            //mainGameLoop();
        }
        else if (command == "win" && (state == "maingameloop" || state == "executeorders")) {
            changeState("win", "Game loop has ended(type 'end' to proceed or 'play' to start a new game)");
        }
        else if ((command == "play" || command == "end") && state == "win") {
            if (command == "play") {
                state = "start";
            }
            else {
                gameOver = true;
                cout << "Exiting game." << endl;
            }
        }
        else {
            cout << "Invalid command for current state: " << state << endl;
        }
    }
}
/**
void GameEngine::mainGameLoop() {
    bool roundOver = false;

    while (!roundOver) {
        reinforcementPhase();
        issueOrdersPhase();
        executeOrdersPhase();

        roundOver = checkWinCondition();
    }
}


// =======================
// Reinforcement Phase
// =======================
void GameEngine::reinforcementPhase() {
    changeState("reinforcement", "Reinforcement Phase.");
    //

    for (auto player: players) {
        //reinforcement

        int territoriesOwned = player->getTerritories().size();
        int reinforcements = territoriesOwned/3; //truncated


        if (reinforcements < 3) {
            reinforcements = 3;
        }



    }

    waitForUser();

}

// =======================
// Issue Orders Phase
// =======================
void GameEngine::issueOrdersPhase() {
    changeState("issueorders", "Issue Orders Phase.");
    //

    for (auto o: players) {
        //issue orders
    }
    waitForUser();
}

// =======================
// Execute Orders Phase
// =======================
void GameEngine::executeOrdersPhase() {
    changeState("executeorders", "Execute Orders Phase.");


    for (auto o: players) {

    }


    waitForUser();
}

bool GameEngine::checkWinCondition() {
    string command;
    cout << "\nChecking Winning condition..." << endl;
    cout << "Enter a command (type 'exit' to end this game loop): ";
    cin >> command;

    if (command == "exit") {
        state = "win";
        return true; // signal game loop to end
    }
    return false;

}
*/
void GameEngine::waitForUser() { //line skips
    cout << "\nPress Enter to continue...";
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    cin.get();
}
