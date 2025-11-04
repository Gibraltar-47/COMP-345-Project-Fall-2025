//
// Created by Howard on 2025-11-03.
//

#include "GameEngine.h"
#include <iostream>

//using namespace std;

// Free function required by the assignment
//void testGameStates() {
   // cout << "===== GAME ENGINE STATE MACHINE TEST =====" << endl;

    //GameEngine engine;   // create a new engine instance
    //engine.run();        // start the game loop

    //cout << "===== GAME ENDED =====" << endl;
//}

// Standard main that just calls testGameStates
//int main() {
    //testGameStates();
    //return 0;
//}


#include "C:\Users\Howard\COMP-345-Project-Fall-2025-PART2\Engine\GameEngine.h"
#include "./Orders/Orders.h"
//#include "./Part-4-Deck/Cards.h"
//#include "./part1-map/Map.h"
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

    GameEngine engine;   // create a new engine instance
    engine.runGame();        // start the game loop

    cout << "===== GAME ENDED =====" << endl;
}

// Standard main that just calls testGameStates
int main() {
    testGameStates();
    return 0;
}
