#include "./Engine/GameEngine.h"
#include "./Orders/Orders.h"
#include "./Part-4-Deck/Cards.h"
#include "./part1-map/Map.h"
#include "./Player/Player.h"
#include <iostream>

using namespace std;

extern void testGameStates();
//extern void testOrdersLists();
//extern void testCards();
//extern void testLoadMap();
//extern void testPlayers();


int main(){
    //testLoadMap();
    //testPlayers();
    //testOrdersLists();
    //testCards();
    testGameStates();

    //return 0;
}


/**
void testGameStates() {
    cout << "===== GAME ENGINE STATE MACHINE TEST =====" << endl;
    Map testMap("TestMap");

    // Create Continents
    Continent* continent1 = new Continent("ContinentA", 5);
    Continent* continent2 = new Continent("ContinentB", 3);
    Continent* continent3 = new Continent("ContinentC", 2);
    Continent* continent4 = new Continent("ContinentD", 4);
    Continent* continent5 = new Continent("ContinentE", 2);
    Continent* continent6 = new Continent("ContinentF", 1);


    // Add continents to map
    testMap.addContinent(continent1);
    testMap.addContinent(continent2);
    testMap.addContinent(continent3);
    testMap.addContinent(continent4);
    testMap.addContinent(continent5);
    testMap.addContinent(continent6);


    // === Continent 1: Northern Reach ===
    Territory* terr1  = new Territory("Territory1",  continent1, 2, 8, {"Territory2", "Territory3"});
    Territory* terr2  = new Territory("Territory2",  continent1, 4, 9, {"Territory1", "Territory4"});
    Territory* terr3  = new Territory("Territory3",  continent1, 3, 7, {"Territory1", "Territory4"});
    Territory* terr4  = new Territory("Territory4",  continent1, 5, 8, {"Territory2", "Territory3", "Territory5"}); // link to continent2

    // === Continent 2: Central Empire ===
    Territory* terr5  = new Territory("Territory5",  continent2, 7, 7, {"Territory4", "Territory6", "Territory7"});
    Territory* terr6  = new Territory("Territory6",  continent2, 8, 6, {"Territory5", "Territory7", "Territory8"});
    Territory* terr7  = new Territory("Territory7",  continent2, 6, 6, {"Territory5", "Territory6", "Territory8"});
    Territory* terr8  = new Territory("Territory8",  continent2, 9, 7, {"Territory6", "Territory7", "Territory9"}); // link to continent3

    // === Continent 3: Southern Isles ===
    Territory* terr9  = new Territory("Territory9",  continent3, 11, 5, {"Territory8", "Territory10", "Territory11"});
    Territory* terr10 = new Territory("Territory10", continent3, 13, 4, {"Territory9", "Territory11"});
    Territory* terr11 = new Territory("Territory11", continent3, 12, 6, {"Territory9", "Territory10", "Territory12"}); // link to continent4
    Territory* terr12 = new Territory("Territory12", continent3, 14, 5, {"Territory11"});

    // === Continent 4: Eastern Dominion ===
    Territory* terr13 = new Territory("Territory13", continent4, 16, 6, {"Territory14", "Territory15", "Territory11"});
    Territory* terr14 = new Territory("Territory14", continent4, 17, 7, {"Territory13", "Territory15", "Territory16"});
    Territory* terr15 = new Territory("Territory15", continent4, 18, 5, {"Territory13", "Territory14", "Territory16"});
    Territory* terr16 = new Territory("Territory16", continent4, 19, 6, {"Territory14", "Territory15", "Territory17"}); // link to continent5

    // === Continent 5: Western Frontier ===
    Territory* terr17 = new Territory("Territory17", continent5, 21, 5, {"Territory16", "Territory18", "Territory19"});
    Territory* terr18 = new Territory("Territory18", continent5, 22, 4, {"Territory17", "Territory19"});
    Territory* terr19 = new Territory("Territory19", continent5, 23, 6, {"Territory17", "Territory18"});


    Territory* terr20 = new Territory("Territory20", continent6, 30, 30, {});


    // === Add territories to continents ===

    // Continent 1: Northern Reach
    continent1->addTerritory(terr1);
    continent1->addTerritory(terr2);
    continent1->addTerritory(terr3);
    continent1->addTerritory(terr4);

    // Continent 2: Central Empire
    continent2->addTerritory(terr5);
    continent2->addTerritory(terr6);
    continent2->addTerritory(terr7);
    continent2->addTerritory(terr8);

    // Continent 3: Southern Isles
    continent3->addTerritory(terr9);
    continent3->addTerritory(terr10);
    continent3->addTerritory(terr11);
    continent3->addTerritory(terr12);

    // Continent 4: Eastern Dominion
    continent4->addTerritory(terr13);
    continent4->addTerritory(terr14);
    continent4->addTerritory(terr15);
    continent4->addTerritory(terr16);

    // Continent 5: Western Frontier
    continent5->addTerritory(terr17);
    continent5->addTerritory(terr18);
    continent5->addTerritory(terr19);

    continent6->addTerritory(terr20);


    // Add territories to map
    testMap.addTerritory(terr1);
    testMap.addTerritory(terr2);
    testMap.addTerritory(terr3);
    testMap.addTerritory(terr4);
    testMap.addTerritory(terr5);
    testMap.addTerritory(terr6);
    testMap.addTerritory(terr7);
    testMap.addTerritory(terr8);
    testMap.addTerritory(terr9);
    testMap.addTerritory(terr10);
    testMap.addTerritory(terr11);
    testMap.addTerritory(terr12);
    testMap.addTerritory(terr13);
    testMap.addTerritory(terr14);
    testMap.addTerritory(terr15);
    testMap.addTerritory(terr16);
    testMap.addTerritory(terr17);
    testMap.addTerritory(terr18);
    testMap.addTerritory(terr19);
    testMap.addTerritory(terr20);

    // Initialize adjacency matrix for the map
    testMap.initAdjMatrix();

    // Set edges (bi-directional adjacency between connected territories)
    testMap.setVertice(terr1, terr2);
    testMap.setVertice(terr2, terr3);
    testMap.setVertice(terr3, terr4);
    testMap.setVertice(terr4, terr5);
    testMap.setVertice(terr5, terr6);
    testMap.setVertice(terr6, terr7);
    testMap.setVertice(terr7, terr8);
    testMap.setVertice(terr8, terr9);
    testMap.setVertice(terr9, terr10);
    testMap.setVertice(terr10, terr11);
    testMap.setVertice(terr11, terr12);
    testMap.setVertice(terr12, terr13);
    testMap.setVertice(terr13, terr14);
    testMap.setVertice(terr14, terr15);
    testMap.setVertice(terr15, terr16);
    testMap.setVertice(terr16, terr17);
    testMap.setVertice(terr17, terr18);
    testMap.setVertice(terr18, terr19);

    // (Optional) a few cross-continent bridges for gameplay balance
    testMap.setVertice(terr4, terr5);   // connect Continent 1 → 2
    testMap.setVertice(terr8, terr9);   // connect Continent 2 → 3
    testMap.setVertice(terr12, terr13); // connect Continent 3 → 4
    testMap.setVertice(terr16, terr17); // connect Continent 4 → 5

    // Print map for verification
    std::cout << testMap << std::endl;

    // Create 5 players
    Player p1("John");
    Player p2("Will");
    Player p3("Bill");
    Player p4("Eve");
    Player p5("Spectator"); // owns none

    // Assign territories manually
    p1.addTerritory(terr1);
    p1.addTerritory(terr2);
    p1.addTerritory(terr3);
    p1.addTerritory(terr4);

    p2.addTerritory(terr5);
    p2.addTerritory(terr6);
    p2.addTerritory(terr7);
    p2.addTerritory(terr8);
    p2.addTerritory(terr9);

    p3.addTerritory(terr10);
    p3.addTerritory(terr11);
    p3.addTerritory(terr12);
    p3.addTerritory(terr13);

    p4.addTerritory(terr14);
    p4.addTerritory(terr15);
    p4.addTerritory(terr16);
    p4.addTerritory(terr17);
    p4.addTerritory(terr18);
    p4.addTerritory(terr19);

    // Set owners accordingly
    auto setOwner = [](Player* p, std::initializer_list<Territory*> terrs) {
        for (auto t : terrs) t->setOwner(p);
    };

    setOwner(&p1, {terr1, terr2, terr3, terr4});
    setOwner(&p2, {terr5, terr6, terr7, terr8, terr9});
    setOwner(&p3, {terr10, terr11, terr12, terr13});
    setOwner(&p4, {terr14, terr15, terr16, terr17, terr18, terr19});

    Deck deck;

    //Add 7 copies of each card type
    vector<string> cardNames = {"Bomb", "Airlift", "Negotiate", "Blockade"};
    for (const auto& name : cardNames) {
        for (int i = 0; i < 20; ++i) {
            deck.addCard(new Card(name));
        }
    }
    for (int i = 0; i < 5; ++i) {
        p1.addCard(deck.draw());
        p2.addCard(deck.draw());
        p3.addCard(deck.draw());
        p4.addCard(deck.draw());
        p5.addCard(deck.draw());

    }



    GameEngine engine;   // create a new engine instance
    engine.addPlayer(&p1);
    engine.addPlayer(&p2);
    engine.addPlayer(&p3);
    engine.addPlayer(&p4);
    engine.addPlayer(&p5);

    engine.addMap(&testMap);
    engine.giveDeck(&deck);

    engine.runGame();        // start the game loop

    cout << "===== GAME ENDED =====" << endl;
}

// Standard main that just calls testGameStates
int main() {
    testGameStates();
    return 0;
*/