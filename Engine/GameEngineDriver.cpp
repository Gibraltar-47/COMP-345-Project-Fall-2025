
#include "GameEngine.h"

#include <iostream>

using namespace std;

 //Free function required by the assignment
void testGameStates() {
    cout << "===== GAME ENGINE STATE MACHINE TEST =====" << endl;

    LogObserver* observer = new LogObserver();
    GameEngine engine(observer);   // create a new engine instance
    engine.runGame();        // start the game loop

    cout << "===== GAME ENDED =====" << endl;
}

 //Standard main that just calls testGameStates
int main() {
    testGameStates();
    return 0;
}