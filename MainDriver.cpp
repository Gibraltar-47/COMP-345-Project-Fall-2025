#include "./Engine/GameEngine.h"
#include "./Orders/Orders.h"
#include "./Part-4-Deck/Cards.h"
#include "./part1-map/Map.h"
#include "./Player/Player.h"

extern void testMainGameLoop();
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
// Standard main that just calls testGameStates
int main() {
    testMainGameLoop();
    return 0;
}