//
// Created by Howard on 2025-11-03.
//
#include "GameEngine.h"
#include <iostream>
#include <limits>
#include <algorithm>
#include <random>

#include "../CommandProcessor/CommandProcessing.h"
#include "../Orders/Orders.h"
#include "../Part-4-Deck/Cards.h"
#include "../part1-map/Map.h"
#include <sstream>
#include <tuple>

using std::string;
using std::cout;
using std::endl;
using std::cin;

static inline std::string trim_copy(std::string s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch){ return !std::isspace(ch); }));
    s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch){ return !std::isspace(ch); }).base(), s.end());
    return s;
}
// returns true if 'line' starts with 'verb' (case-sensitive) followed by either space or end
static inline bool starts_with_verb(const std::string &line, const std::string &verb) {
    if (line.size() < verb.size()) return false;
    if (line.rfind(verb, 0) != 0) return false;
    if (line.size() == verb.size()) return true;            // exact match
    return std::isspace(static_cast<unsigned char>(line[verb.size()])); // followed by space
}
// returns the trimmed remainder after the verb, or empty string if none
static inline std::string arg_after(const std::string &line, const std::string &verb) {
    if (!starts_with_verb(line, verb)) return "";
    std::string rest = line.substr(verb.size());
    return trim_copy(rest);
}

GameEngine::GameEngine(Observer* observer) : state("start"), gameOver(false),map(nullptr), deck(nullptr)
{
    Subject::addObserver(observer);
    GameEngine::notify(*this);
}

GameEngine::GameEngine(const GameEngine& other)  : Subject(other) {
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
        this->observer_ = other.observer_;

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
    return *this;
}
GameEngine::~GameEngine() {
    delete map;
    for (auto* player: players) {
        delete player;
    }
    delete deck;
}

string GameEngine::stringToLog()
{
    string str="The state of the game has changed!\nState:\t"+state;
    return str;
}

void GameEngine::notify(ILoggable& subject)
{
    Subject::observer_->update(subject);
}

string GameEngine::getState() const {
    return state;
}
void GameEngine::changeState(const string& newState, const string& message) {
    state = newState;
    cout << message << endl;
    cout << "Now in state: " << state << endl;
    notify(*this);
}

void GameEngine::startupPhase()
{
    cout << "Welcome to the Game Engine!" << endl << endl;
    cout << "---------------------" << endl;

    int choice;
    bool invalidInput = false;
    gameOver = false;

    while (!invalidInput){
        cout << "Start by choosing whether you want to start the game set up through (1) Console, or through a (2) Text file"<<endl;
        cin >> choice;

        switch(choice)
        {
        case 1:
            {
                auto* console= new CommandProcessor(this->observer_);
                Command* command;
                string input;
                string filename;

                while (!gameOver)
                {
                    command = console->getCommand(this->state);
                    //if the command is invalid, the prompt will be run until a valid command is entered
                    while (command==nullptr){
                        cout<<"The command entered was invalid, please try again!"<<endl;
                        command = console->getCommand(this->state);
                    }

                    input=command->getCommand();
                    //compares command input and gamestate
                    if (input == "exit") { //quick exit
                        gameOver = true;
                        delete console;
                        delete command;
                    }
                    else if (starts_with_verb(input, "loadmap") && (state == "start" || state == "maploaded")) {

                        filename = arg_after(input, "loadmap");
                        if (filename.empty()) {
                            cout << "Missing filename for loadmap\n";
                        } else {
                            MapLoader maploader;
                            cout<<filename<<endl;
                            this->addMap(new Map(maploader.loadMap(filename)));
                            command->saveEffect();
                            string message = "Map "+ filename+" is now loaded!\n(Type 'validatemap' to proceed)\n\n";
                            changeState("maploaded", message);
                        }
                    }
                    else if (input == "validatemap" && state == "maploaded") {

                        if(this->map->validate())
                        {
                            command->saveEffect();
                            string message = "Map "+ filename+" is now validated!\n(Type 'addplayer' to proceed)\n\n";
                            changeState("mapvalidated", message);
                        }else cout<<"Map validation failed! Please load another map again!"<<endl;
                    }
                    else if (starts_with_verb(input,"addplayer") && (state == "mapvalidated" || state == "playersadded")) {
                        string name;
                        name = arg_after(input,"addplayer");
                        if (name.empty()) {
                            cout << "Missing player name for addplayer\n";
                        } else {
                            this->addPlayer(new Player(name));
                            command->saveEffect();
                            string message = "Player "+ name+" is now added!\n(Type 'gamestart' to proceed)\n\n";
                            changeState("playersadded", message);
                        }
                    }
                    else if (input == "gamestart" && state == "playersadded") {

                        command->saveEffect();
                        changeState("maingameloop", "Game loop has begun (press 'enter' to proceed)\n\n");

                        int numPlayer = static_cast<int>(this->players.size());
                        int numTerr = static_cast<int>(this->map->getTerritories().size());
                        int numCards = numPlayer * 5;
                        int randomIndex;
                        bool unowned;

                        //Add 5 * numberOfPlayer copies of each card type
                        vector<string> cardNames = {"Bomb", "Airlift", "Negotiate", "Blockade"};
                        for (const auto& name : cardNames) {
                            for (int i = 0; i < numCards; ++i) {
                                deck->addCard(new Card(name));
                            }
                        }

                        int territoryPerPlayer = numTerr / numPlayer;
                        int terrLeft = numTerr % numPlayer;

                        std::random_device rd;
                        std::mt19937 g(rd());

                        // Shuffle the vector of players to randomize the order
                        shuffle(this->players.begin(), this->players.end(), g);

                        for (Player* player : this->players)
                        {
                            //assign the correct number of territories per player
                            for (int i=0;i<territoryPerPlayer;i++)
                            {
                                unowned=true;

                                //choose random number corresponds to index to territory
                                //continue to randomize the territory until an unowned territory is found
                                while (unowned){
                                    randomIndex= rand() % numTerr;
                                    if (map->getTerritories()[randomIndex]->getOwner()==nullptr)
                                    {
                                        map->getTerritories()[randomIndex]->setOwner(player);
                                        player->addTerritory(map->getTerritories()[randomIndex]);
                                        unowned=false;
                                    }
                                }
                            }

                            //give every player 50 army unit
                            player->addNumArmies(50);
                            //make the player draw a card twice
                            player->getHand()->draw(*this->deck);
                            player->getHand()->draw(*this->deck);

                        }

                        cout<<"All players have now each received 50 units of armies, 2 cards and "<<territoryPerPlayer<<" territories!"<<endl;

                        //PART TO ADD WHEN MERGING WITH SHAWN'S PART, PART4 ITERATION 2
                        // //adding the neutral player
                        // this->addPlayer(new Player("Neutral Player"));
                        // //ORDERBLOCKADE::NEUTRALPLAYER=NEUTRALPLAYER;
                        //
                        // //if there are leftover territories then they are given to the neutral player
                        // if (terrLeft != 0)
                        // {
                        //     for (Territory* territory : this->map->getTerritories())
                        //     {
                        //         if (territory->getOwner() == nullptr)
                        //         {
                        //             //setting the owner as the last player added to the vector (neutral player)
                        //             territory->setOwner(this->players.back());
                        //         }
                        //     }
                        // }

                        mainGameLoop();
                    }
                    else if ((input == "replay" || input == "end") && state == "win") {
                        if (input == "replay") {
                            state = "start";
                            command->saveEffect();
                        }
                        else {
                            gameOver = true;
                            cout << "Exiting game." << endl;
                            command->saveEffect();
                            delete console; //
                            delete command;
                        }
                    }
                }

                invalidInput = true;
                break;
            }
        case 2:
            {
                cout << "You have chosen to use a text file for the startup phase!\nEnter the file name in the following format filename.txt :\n"<<endl;
                string filename;
                cin >> filename;
                auto* textFile= new FileCommandProcessorAdapter(this->observer_, filename);
                Command* command;
                string input;
                while (!gameOver)
                {
                    command = textFile->getCommand(this->state);
                    //if the command is invalid, the prompt will be run until a valid command is entered
                    while (command==nullptr){
                        cout<<"The command entered was invalid, please try again!"<<endl;
                        command = textFile->getCommand(this->state);
                    }
                    input= command->getCommand();
                    //compares command input and gamestate
                    if (input == "exit") { //quick exit
                        gameOver = true;
                        delete textFile;
                        delete command;
                    }
                    else if (starts_with_verb(input, "loadmap") && (state == "start" || state == "maploaded")) {

                        filename = arg_after(input, "loadmap");
                        if (filename.empty()) {
                            cout << "Missing filename for loadmap\n";
                        } else {
                            MapLoader maploader;
                            cout<<filename<<endl;
                            this->addMap(new Map(maploader.loadMap(filename)));
                            command->saveEffect();
                            string message = "Map "+ filename+" is now loaded!\n(Type 'validatemap' to proceed)\n\n";
                            changeState("maploaded", message);
                        }
                    }
                    else if (input == "validatemap" && state == "maploaded") {

                        if(this->map->validate())
                        {
                            command->saveEffect();
                            string message = "Map "+ filename+" is now validated!\n(Type 'addplayer' to proceed)\n\n";
                            changeState("mapvalidated", message);
                        }else cout<<"Map validation failed! Please load another map again!"<<endl;
                    }
                    else if (starts_with_verb(input,"addplayer") && (state == "mapvalidated" || state == "playersadded")) {
                        string name;
                        name = arg_after(input,"addplayer");
                        if (name.empty()) {
                            cout << "Missing player name for addplayer\n";
                        } else {
                            this->addPlayer(new Player(name));
                            command->saveEffect();
                            string message = "Player "+ name+" is now added!\n(Type 'gamestart' to proceed)\n\n";
                            changeState("playersadded", message);
                        }
                    }
                    else if (input == "gamestart" && state == "playersadded") {

                        command->saveEffect();
                        changeState("maingameloop", "Game loop has begun (press 'enter' to proceed)\n\n");

                        int numPlayer = static_cast<int>(this->players.size());
                        int numTerr = static_cast<int>(this->map->getTerritories().size());
                        int numCards = numPlayer * 5;
                        int randomIndex;
                        bool unowned;

                        //Add 5 * numberOfPlayer copies of each card type
                        vector<string> cardNames = {"Bomb", "Airlift", "Negotiate", "Blockade"};
                        for (const auto& name : cardNames) {
                            for (int i = 0; i < numCards; ++i) {
                                deck->addCard(new Card(name));
                            }
                        }

                        int territoryPerPlayer = numTerr / numPlayer;
                        int terrLeft = numTerr % numPlayer;

                        std::random_device rd;
                        std::mt19937 g(rd());

                        // Shuffle the vector of players to randomize the order
                        shuffle(this->players.begin(), this->players.end(), g);

                        for (Player* player : this->players)
                        {
                            //assign the correct number of territories per player
                            for (int i=0;i<territoryPerPlayer;i++)
                            {
                                unowned=true;

                                //choose random number corresponds to index to territory
                                //continue to randomize the territory until an unowned territory is found
                                while (unowned){
                                    randomIndex= rand() % numTerr;
                                    if (map->getTerritories()[randomIndex]->getOwner()==nullptr)
                                    {
                                        map->getTerritories()[randomIndex]->setOwner(player);
                                        player->addTerritory(map->getTerritories()[randomIndex]);
                                        unowned=false;
                                    }
                                }
                            }

                            //give every player 50 army unit
                            player->addNumArmies(50);
                            //make the player draw a card twice
                            player->getHand()->draw(*this->deck);
                            player->getHand()->draw(*this->deck);

                        }

                        cout<<"All players have now each received 50 units of armies, 2 cards and "<<territoryPerPlayer<<" territories!"<<endl;

                        //PART TO ADD WHEN MERGING WITH SHAWN'S PART, PART4 ITERATION 2
                        // //adding the neutral player
                        // this->addPlayer(new Player("Neutral Player"));
                        // //ORDERBLOCKADE::NEUTRALPLAYER=NEUTRALPLAYER;
                        //
                        // //if there are leftover territories then they are given to the neutral player
                        // if (terrLeft != 0)
                        // {
                        //     for (Territory* territory : this->map->getTerritories())
                        //     {
                        //         if (territory->getOwner() == nullptr)
                        //         {
                        //             //setting the owner as the last player added to the vector (neutral player)
                        //             territory->setOwner(this->players.back());
                        //         }
                        //     }
                        // }

                        mainGameLoop();
                    }
                    else if ((input == "replay" || input == "end") && state == "win") {
                        if (input == "replay") {
                            state = "start";
                            command->saveEffect();
                        }
                        else {
                            gameOver = true;
                            cout << "Exiting game." << endl;
                            command->saveEffect();
                            delete textFile; //
                            delete command;
                        }
                    }

                }
                invalidInput = true;
                break;
            }
        default:
            cout << "Invalid input!" << endl;
        }
    }
}

void GameEngine::runGame() {

    Deck* deckTemp = new Deck();
    this->deck = deckTemp;

    startupPhase();

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

        executeOrdersPhase();
        printAllPlayerOrders(players);
        if (checkWinCondition(players, map) ){
            roundOver = true;
        }

    }
}


// =======================
// Reinforcement Phase
// =======================
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

    waitForUser();
}

// =======================
// Issue Orders Phase
// =======================
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
            cout << "\n" << player->getName() << " territories to defend:\n";
            for (auto* t : player->toDefend(map->getTerritories())) cout << "  - " << t->getName() << endl;

            cout << player->getName() << " territories to attack:\n";
            for (auto* t : player->toAttack(map->getTerritories())) cout << "  - " << t->getName() << endl;


            //Prompts user for a choice
            cout << "\nPlayer " << player->getName() << ", issue an order:\n";
            cout << "1. Deploy\n2. Advance\n3. Bomb\n4. Blockade\n5. Airlift\n6. Negotiate\n7. Finish issuing\nChoice: ";
            int choice;
            cin >> choice;


            //Done issuing Orders.int choice;
            if (!(cin >> choice)) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input. Please enter a number.\n";
                cout << "Skipping your turn.\n";
                playerDone[i] = true;
                continue;
            }

            if (choice == 7) {
                playerDone[i] = true;
                cout << player->getName() << " is done issuing orders.\n";
                continue;
            }

            if (choice < 1 || choice > 7) {
                cout << "Invalid choice. Please try again.\n";
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
                    cout << "Invalid territories.\n";
                    continue;
                }
            } else if (choice == 1 || choice == 4) { //if requires one location
                string terrName;
                cout << "Enter territory name: ";
                cin >> terrName;
                source = player->findTerritoryByName(terrName);
                if (!source) {
                    cout << "Invalid territory.\n";
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
            cout << "Order issued successfully!\n";

            allDone = false; // player can make another action after this current one + turn order wait


        }
        //checks if all players are done issuing orders, else continue loop
        allDone = std::all_of(playerDone.begin(), playerDone.end(), [](bool done){ return done; });
    }
    cout << "All players have finished issuing orders." << endl;
    waitForUser();
}
// =======================
// Execute Orders Phase
// =======================
void GameEngine::executeOrdersPhase() {
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
    waitForUser();
}
//Might need to change this method, but it works for now :|
bool GameEngine::checkWinCondition(const std::vector<Player*>& players, Map* map) { //checks to see if any player has won

    cout << "\nChecking win condition..." << endl;

    //checks if players or map is missing
    if (players.empty() || !map) {
        cout << "Invalid players or map.\n";
        return false;
    }
    //checks if map is empty
    const vector<Territory*>& allTerritories = map->getTerritories();
    if (allTerritories.empty()) {
        cout << "No territories in map.\n";
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
            cout << "\nPlayer " << player->getName() << " controls the entire map!" << endl;
            state = "win";
            return true;
        }
    }

    cout << "No winner yet.\n";
    return false;
}

void GameEngine::waitForUser() { //line skips kinda wonky for now
    cout << "\nPress Enter to continue...";
    // Clear any leftover junk before waiting
    if (cin.peek() == '\n')
        cin.ignore(); // eat the leftover newline only
    cin.get();
    cout<< endl;
}

void GameEngine::addMap(Map* map) { //adds a map to the engine
    this->map = map;
}
void GameEngine::addPlayer(Player *player) { //adds a player to the engine
    this->players.push_back(player);
}

void GameEngine::removePlayer(Player* player) { //to be implemented
    if (!player) return;

    auto it = std::find(this->players.begin(), this->players.end(), player);
    if (it != this->players.end()) {
        cout << "Player " << player->getName() << " removed.\n";

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

        cout << "\nPlayer: " << player->getName() << endl;

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


