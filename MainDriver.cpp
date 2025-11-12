#include "./Engine/GameEngine.h"
#include "./Orders/Orders.h"
#include "./Part-4-Deck/Cards.h"
#include "./part1-map/Map.h"
#include "./Player/Player.h"

extern void testManualCommands();
extern void testCommandProcessor();
extern void testFileCommandProcessorAdapter();
extern void testOrderExecution();
extern void testGameStates();
extern void testMainGameLoop();

int main(){
    testCommandProcessor();
    testGameStates();
    testMainGameLoop();
    testOrderExecution();


    return 0;
}