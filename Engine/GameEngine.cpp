//
// Created by Howard on 2025-11-03.
//
#include "GameEngine.h"
#include <iostream>
#include <limits>
#include <algorithm>

#include "../Orders/Orders.h"
#include "../Part-4-Deck/Cards.h"

using std::string;
using std::cout;
using std::endl;
using std::cin;

GameEngine::GameEngine() : state("start"), gameOver(false),map(nullptr), deck(nullptr) {}
GameEngine::GameEngine(const GameEngine& other){
    this->state = other.state;
    this->gameOver = other.gameOver;


    for (Player* player: other.players) {
        this->players.push_back(new Player(*player));
    }
    this->map = other.map;
    this->deck = other.deck;

};
GameEngine& GameEngine::operator=(const GameEngine& other) {
    if (this != &other) {
        this->state = other.state;
        this->gameOver = other.gameOver;

        for (Player* player: players) {
            delete player;
        }
        players.clear();
        delete map;
        for (const Player* player: other.players) {
            this->players.push_back(new Player(*player));
        }

        this->map = other.map;
    }
}

GameEngine::~GameEngine() { //could use improvements (rn for testing, it is manually adding items to the engine, no need to delete)
    map = nullptr;
    for (auto* player: players) {
        player = nullptr;
    }
    deck = nullptr;
}

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
    state = "playersadded"; //change it to start for actual use (start of program), this is changed for skipping the startup phase and all
    gameOver = false;

    while (!gameOver) {
        cout << "Current State: " << getState() << endl;
        cout << "Enter a command:";
        cin >> command;

        //compares command input and gamestate
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
            changeState("playersadded", "Players added.(type 'gamestart' to proceed)");
        }
        else if (command == "gamestart" && state == "playersadded") {
            changeState("maingameloop", "Game loop has begun(press 'enter' to proceed)");
            mainGameLoop();
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

ostream& operator<<(ostream& out, const GameEngine& engine) {
    out << "GameEngine State: " << engine.state << "\n"
        << "Game Over: " << (engine.gameOver ? "Yes" : "No") << "\n"
        << "Players Count: " << engine.players.size() << "\n"
        << "Map: " << (engine.map ? "Loaded" : "None") << "\n";
    return out;
}

//==================================
//Part 2
void GameEngine::mainGameLoop() {
    bool roundOver = false; //gameloop check
    while (!roundOver) {
        reinforcementPhase();

        issueOrdersPhase(players,map);
        printAllPlayerOrders(players);
        //executeOrdersPhase();
        //printAllPlayerOrders(players);


        if (executeOrdersPhase()) {
            roundOver = true;

        }

    }
}

void GameEngine::reinforcementPhase() {
    changeState("reinforcement", "Reinforcement Phase.");

    if (!map) { //if map is missing skip
        cout << "No map loaded, skipping reinforcements." << endl;
        return;
    }

    // take continents by value (avoid binding to a temporary reference)
    const auto& continents = map->getContinents();

    cout << "\n=== Reinforcement Phase Debug ===" << endl;


    for (Player* p : players) {
        if (!p) continue; //skip if missing


        int startArmies = p->getNumArmies(); //before reinforcement
        int territoryCount = static_cast<int>(p->getTerritories().size());

        // base reinforcement: floor(#territories / 3), minimum 3
        int baseReinforcements = territoryCount / 3;
        if (baseReinforcements < 3) baseReinforcements = 3;

        // continent control bonuses
        int continentBonus = 0;
        std::vector<std::string> ownedContinents;

        for (Continent* cont : continents) {
            if (!cont) continue;

            const auto& contTerritories = cont->getTerritories();
            if (contTerritories.empty()) continue;

            bool ownsAll = true;
            for (Territory* t : contTerritories) {
                if (!t->getOwner() || (t->getOwner() != p && t->getOwner()->getName() != p->getName())) {
                    ownsAll = false;
                    break;
                }
            }

            if (ownsAll) {
                int bonus = cont->getPointsToConquer();
                continentBonus += bonus;
                ownedContinents.push_back(cont->getName() + " (+" + std::to_string(bonus) + ")");
            }
        }

        int totalReinforcements = baseReinforcements + continentBonus;

        // Debug output before applying
        cout << "\nPlayer: " << p->getName()
             << " | Territories: " << territoryCount
             << " | Start armies: " << startArmies << endl;
        cout << "  Base from territories: " << baseReinforcements << endl;
        cout << "  Continent bonus total: " << continentBonus << endl;
        cout << "  Total reinforcements to add: " << totalReinforcements << endl;

        if (!ownedContinents.empty()) {
            cout << "  Controls continents: ";
            for (size_t i = 0; i < ownedContinents.size(); ++i) {
                cout << ownedContinents[i];
                if (i < ownedContinents.size() - 1) cout << ", ";
            }
            cout << endl;
        }

        // add to player's reinforcement pool
        p->addNumArmies(totalReinforcements);

        // Debug after applying
        cout << "  New army pool: " << p->getNumArmies() << endl;
    }


    cout << "=== End Reinforcement Debug ===\n" << endl;

}


void GameEngine::issueOrdersPhase(vector<Player*>& players , Map* map) {

    changeState("issueorders", "Issue Orders Phase.");

    bool allDone = false;
    vector<bool> playerDone(players.size(),false); //needed for player skips



    while (!allDone) {
        allDone = true; //assumes no action taken by player until proven otherwise

        for (size_t i = 0; i < players.size(); i++) {
            //current turn player
            Player* player = players[i];
            if (playerDone[i]) { //player skips check
                continue;
            }
            cout << "\n" << player->getName() << " territories to defend: " << endl;
            for (auto* t : player->toDefend(map->getTerritories())) cout << "  - " << t->getName() << endl;

            cout << player->getName() << " territories to attack:" << endl;
            for (auto* t : player->toAttack(map->getTerritories())) cout << "  - " << t->getName() << endl;


            //Prompts user for a choice
            int choice;

            //Done issuing Orders.int choice;
            while (true) {
                cout << "\nPlayer " << player->getName() << " has " << player->getNumFreeArmies() << " free army units (" <<  player->getNumArmies() <<" total army units). Please issue an order:\n";
                cout << "1. Deploy\n2. Advance\n3. Bomb\n4. Blockade\n5. Airlift\n6. Negotiate\n7. Finish issuing\nChoice: ";

                if (!(cin >> choice)) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Invalid input. Please enter a number." << endl;
                    cout << "Skipping your turn." << endl;
                    playerDone[i] = true;
                    continue;
                }

                if (choice == 8) {
                    cout << "Exiting order issuance." << endl;
                    state = "win";
                    return;
                }

                if (player->getNumFreeArmies() > 0 && choice != 1 && choice != 7) {
                    cout << "You still have " << player->getNumArmies()
                         << " undeployed armies. You must deploy them before issuing other orders." << endl;
                    continue;
                }

                if (choice < 1 || choice > 8) {
                    cout << "Invalid choice. Please try again." << endl;
                    continue;
                }
                break;
            }


            if (choice == 7) {
                playerDone[i] = true;
                cout << player->getName() << " is done issuing orders." << endl;
                continue;
            }

            //Pick territories
            Territory* source = nullptr;
            Territory* target = nullptr;
            Player* targetPlayer = nullptr;

            //Checks for the necessary parameters
            if (choice != 1 && choice != 4 && choice != 6) { //if requires two location
                string sourceName, targetName;
                cout << "Enter source territory name: ";
                cin >> sourceName;
                cout << "Enter target territory name: ";
                cin >> targetName;

                source = player->findTerritoryByName(sourceName);
                target = map->getTerritory(targetName);

                if (!source || !target) {
                    cout << "Invalid territories." << endl;
                    continue;
                }
            } else if (choice == 1 || choice == 4) { //if requires one location
                string terrName;
                cout << "Enter territory name: ";
                cin >> terrName;
                source = player->findTerritoryByName(terrName);
                if (!source) {
                    cout << "Invalid territory." << endl;
                    continue;
                }
            } else if (choice == 6) { //if requires a 2nd player name
                string otherPlayerName;
                cout << "Enter other player name: ";
                cin >> otherPlayerName;
                for (auto* p : players)
                    if (p->getName() == otherPlayerName)
                        targetPlayer = p;
            }
            //Insert a number of army to send out
            int armies = 0;
            if (choice == 1 || choice == 2 || choice == 5) {
                cout << "Enter number of armies: ";
                cin >> armies;
            }

            //creation of the order
            player->issueOrder(*deck,choice, source, armies, target, *targetPlayer);
            cout << "Order issued successfully!" << endl;

            allDone = false; // player can make another action after this current one + turn order wait


        }
        //checks if all players are done issuing orders, else continue loop
        allDone = std::all_of(playerDone.begin(), playerDone.end(), [](bool done){ return done; });
    }
    cout << "All players have finished issuing orders." << endl;
}

bool GameEngine::executeOrdersPhase() {
    changeState("executeorders", "Execute Orders Phase.");
    bool ordersRemaining = true;
    while (ordersRemaining) {
        ordersRemaining = false;
        //round-robin style
        for (auto player : players) {
            OrdersList* ol = player->getOrderList();
            std::list<Orders*> &orders = ol->getList(); // reference to the actual list

            if (!orders.empty()) {
                Orders* nextOrder = orders.front();
                orders.pop_front();  // remove from the list

                std::cout << player->getName() << " executing order: " << *nextOrder << std::endl;
                //validate()
                nextOrder->execute();

                ordersRemaining = true; // we executed at least one order
            }
        }
    }
    //removes eliminated players
    std::vector<Player*> eliminated;
    for (auto* player : players) {
        if (player->getTerritories().empty()) {
            eliminated.push_back(player);
        }
    }

    for (auto* player : eliminated) {
        player->getHand()->returnAll(*deck);
        removePlayer(player);
    }
    cout << endl;

    if (checkWinCondition(players, map)) {
        return true;
    }


    int exitCode = 0;
    //for testing and faster exits
    cout << "If you want to exit the game loop, enter 1. To continue, enter 0: ";
    cin >> exitCode;
    if (exitCode == 1) {
        return true;
    }

    return false;
}
//Might need to change this method, but it works for now :|
bool GameEngine::checkWinCondition(const std::vector<Player*>& players, Map* map) { //checks to see if any player has won
    cout << endl;
    cout << "Checking win condition..." << endl;

    //checks if players or map is missing
    if (players.empty() || !map) {
        cout << "Invalid players or map." << endl;
        return false;
    }
    //checks if map is empty
    const vector<Territory*>& allTerritories = map->getTerritories();
    if (allTerritories.empty()) {
        cout << "No territories in map." << endl;
        return false;
    }
    //total number of territory
    int totalTerritories = static_cast<int>(allTerritories.size());
    cout << "Total territories: " << totalTerritories << endl;

    //Loop through players and count how many territories each owns
    for (auto* player : players) {
        if (!player) continue;

        int ownedCount = static_cast<int>(player->getTerritories().size());
        cout <<  player->getName() << " owns " << ownedCount << " territories." << endl;

        // Win condition: owns all territories
        if (ownedCount == totalTerritories) {
            cout << "Player " << player->getName() << " controls the entire map!" << endl;
            state = "win";
            return true;
        }
    }

    cout << "No winner yet." << endl;
    return false;
}

void GameEngine::addMap(Map* map) { //adds a map to the engine
    this->map = map;
}
void GameEngine::addPlayer(Player *player) { //adds a player to the engine
    this->players.push_back(player);
}

void GameEngine::removePlayer(Player* player) { //to be implemented
    if (!player) return;

    auto it = std::find(players.begin(), players.end(), player);
    if (it != this->players.end()) {
        cout << "Player " << player->getName() << " removed." << endl;
        //delete *it; // Free memory
        players.erase(it);
    }
}

void GameEngine::giveDeck(Deck* deck) {
    this->deck = deck;
}

void GameEngine::printAllPlayerOrders(const std::vector<Player*>& players) { //shows all the orders of all players
    cout << "======= PLAYER ORDER LISTS =======" << endl;
    for (const auto& player : players) {
        if (!player) continue;
        cout << endl;
        cout << "Player: " << player->getName() << endl;

        OrdersList* ol = player->getOrderList();
        if (!ol) {
            cout << "  No OrdersList found." << endl;
            continue;
        }

        const std::list<Orders*>& orders = ol->getList();
        if (orders.empty()) {
            cout << "  No orders in list." << endl;
            continue;
        }

        int i = 1;
        for (auto o : orders) {
            if (o)
                cout << "  [" << i++ << "] " << *o << endl;
            else
                cout << "  [" << i++ << "] (null order)" << endl;
        }
    }
    cout << "===================================" << endl;
}


