#include "./Engine/GameEngine.h"
#include "./Orders/Orders.h"
#include "./Part-4-Deck/Cards.h"
#include "./part1-map/Map.h"
#include "./Player/Player.h"

//extern void testGameStates();
//extern void testOrdersLists();
//extern void testCards();
//extern void testLoadMap();
//extern void testPlayers();


//int main(){
    //testLoadMap();
    //testPlayers();
    //testOrdersLists();
    //testCards();
    //testGameStates();

    //return 0;
//}

#include <iostream>

using namespace std;

// Free function required by the assignment
void testGameStates() {
    cout << "===== GAME ENGINE STATE MACHINE TEST =====" << endl;
    Map testMap("TestMap");

    // Create Continents
    Continent* continent1 = new Continent("ContinentA", 5);
    Continent* continent2 = new Continent("ContinentB", 3);

    // Add continents to map
    testMap.addContinent(continent1);
    testMap.addContinent(continent2);

    // Create Territories
    Territory* terr1 = new Territory("Territory1", continent1, 0, 0, {"Territory2", "Territory3"});
    Territory* terr2 = new Territory("Territory2", continent1, 1, 0, {"Territory1"});
    Territory* terr3 = new Territory("Territory3", continent2, 0, 1, {"Territory1"});
    Territory* terr4 = new Territory("Territory4", continent2, 1, 1, {});

    // Add territories to continents
    continent1->addTerritory(terr1);
    continent1->addTerritory(terr2);
    continent2->addTerritory(terr3);
    continent2->addTerritory(terr4);

    // Add territories to map
    testMap.addTerritory(terr1);
    testMap.addTerritory(terr2);
    testMap.addTerritory(terr3);
    testMap.addTerritory(terr4);

    // Initialize adjacency matrix
    testMap.initAdjMatrix();
    continent1->initAdjMatrix();
    continent2->initAdjMatrix();

    // Set edges in adjacency matrix
    testMap.setVertice(terr1, terr2);
    testMap.setVertice(terr1, terr3);
    continent1->setVertice(terr1, terr2);
    continent2->setVertice(terr3, terr4);

    // Print map for verification
    std::cout << testMap << std::endl;

    Player p1("john");
    Player p2("will");
    Player p3("bill");

    p1.addTerritory(terr1);
    p1.addTerritory(terr2);
    p1.addTerritory(terr3);
    p1.addTerritory(terr4);
    Deck deck;

    //Add 7 copies of each card type
    vector<string> cardNames = {"Bomb", "Airlift", "Negotiate", "Blockade"};
    for (const auto& name : cardNames) {
        for (int i = 0; i < 7; ++i) {
            deck.addCard(new Card(name));
        }
    }
    for (int i = 0; i < 5; ++i) {
        p1.addCard(deck.draw());
        p2.addCard(deck.draw());
        p3.addCard(deck.draw());
    }



    GameEngine engine;   // create a new engine instance
    engine.addPlayer(&p1);
    engine.addPlayer(&p2);
    engine.addPlayer(&p3);
    engine.addMap(&testMap);
    engine.giveDeck(&deck);

    engine.runGame();        // start the game loop

    cout << "===== GAME ENDED =====" << endl;
}

// Standard main that just calls testGameStates
int main() {
    testGameStates();
    return 0;
}