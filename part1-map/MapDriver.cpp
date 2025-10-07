#include "Map.h"
#include <iostream>
#include <vector>
#include <filesystem>
using std::cout;

void testLoadMap(){
    MapLoader mapLoader;
    Map map1=mapLoader.loadMap("../part1-map/mapFiles/Antarctica.map");
    if (map1.validate())
    {
        cout<<std::endl<<"Map "<<map1.getName()<<" was validated and will now be printed below!"<<std::endl<<std::endl<<map1;
    }

    Map map2=mapLoader.loadMap("../part1-map/mapFiles/Annys Piratenwelt.map");
    if (map2.validate())
    {
        cout<<std::endl<<"Map "<<map2.getName()<<" was validated and will now be printed below!"<<std::endl<<std::endl<<map2;
    }
}

int main()
{
    testLoadMap();
}