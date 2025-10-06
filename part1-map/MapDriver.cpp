#include "Map.h"
#include <iostream>
#include <vector>
using std::cout;

void testLoadMap(){
    MapLoader mapLoader;
    const Map map1=mapLoader.loadMap("Andorra.map");
    cout<<map1;
}

int main(){
    testLoadMap();
    return 0;
}