#include "Map.h"
#include <iostream>
#include <vector>
#include <filesystem>
using std::cout;
using std::endl;

// void testLoadMap(){
//     MapLoader mapLoader;
//     Map map1=mapLoader.loadMap("./part1-map/mapFiles/Antarctica.map");
//     if (map1.validate())
//     {
//         cout<<std::endl<<"Map "<<map1.getName()<<" was validated and will now be printed below!"<<std::endl<<std::endl<<map1;
//     }

//     Map map2=mapLoader.loadMap("./part1-map/mapFiles/Annys Piratenwelt.map");
//     if (map2.validate())
//     {
//         cout<<std::endl<<"Map "<<map2.getName()<<" was validated and will now be printed below!"<<std::endl<<std::endl<<map2;
//     }
// }
void testLoadMap()
{
    MapLoader mapLoader;

    cout<<"TESTING THE LOADMAP() AND VALIDATE() FUNCTIONS ON VALID MAP FILE : Antarctica.map & Annys Piratenwelt.map"<<endl<<"IF MAP IS VALID, A CONFIRMATION WILL BE PRINTED IN CONSOLE AND THE MAP OBJ WILL BE PRINTED"<<endl<<endl;
    Map map1=mapLoader.loadMap("./part1-map/mapFiles/Antarctica.map");
    if (map1.validate())
    {
        cout<<std::endl<<"Map "<<map1.getName()<<" was validated and will now be printed below!"<<std::endl<<std::endl<<map1<<endl;
    }

    Map map2=mapLoader.loadMap("./part1-map/mapFiles/Annys Piratenwelt.map");
    if (map2.validate())
    {
        cout<<std::endl<<"Map "<<map2.getName()<<" was validated and will now be printed below!"<<std::endl<<std::endl<<map2<<endl;
    }

    cout<<"TESTING THE LOADMAP() AND VALIDATE() FUNCTIONS ON INVALID FILE : fakeFile.txt"<<endl<<"IF MAP IS VALID, A CONFIRMATION WILL BE PRINTED IN CONSOLE AND THE MAP OBJ WILL BE PRINTED"<<endl<<endl;
    Map map3=mapLoader.loadMap("./part1-map/mapFiles/fakeFile.txt");
    if (map3.validate()){
        cout<<std::endl<<"Map "<<map3.getName()<<" was validated and will now be printed below!"<<std::endl<<std::endl<<map3<<endl;
    }

    cout<<endl<<endl<<"TESTING THE VALIDATE() & COPY CONSTRUCTOR AND ASSIGNMENT OPERATION & DESTRUCTOR FUNCTIONS ON MAP OBJECT "<<endl<<"(MAP is connected but the territories don't have a continent)"<<endl<<"IF MAP IS VALID, A CONFIRMATION WILL BE PRINTED IN CONSOLE AND THE MAP OBJ WILL BE PRINTED"<<endl<<endl;

    Map map4("West Island");

    auto* terr1 = new Territory("Pointe-Claire", nullptr, 0, 1, {"Kirkland"});

    map4.addTerritory(terr1);

    Territory terr2("Kirkland",nullptr,0,1,{"Pointe-Claire"});
    //proof of deep copy working
    *terr1=terr2;

    map4.addTerritory(terr1);

    if (map4.validate())
    {
        cout<<std::endl<<"Map "<<map4.getName()<<" was validated and will now be printed below!"<<std::endl<<std::endl<<map4<<endl;
    }else cout<<std::endl<<"Map "<<map4.getName()<<" was NOT validated!"<<std::endl<<std::endl<<map4<<endl;

    cout<<endl<<endl<<"TESTING THE VALIDATE() & COPY CONSTRUCTOR AND ASSIGNMENT OPERATION & DESTRUCTOR FUNCTIONS ON MAP OBJECT "<<endl<<"(MAP is connected but the territories don't have a continent)"<<endl<<"IF MAP IS VALID, A CONFIRMATION WILL BE PRINTED IN CONSOLE AND THE MAP OBJ WILL BE PRINTED"<<endl<<endl;

    Map map5("West Island");

    auto* continent1= new Continent("Montreal",3);
    Continent continent2("Dorval",2);
    *continent1=continent2;
    map5.addContinent(continent1);
    terr1->setContinent(map5.getContinent("Dorval"));
    map5.addTerritory(terr1);
    map5.getContinent("Dorval")->addTerritory(map5.getTerritory("Kirkland"));

    Territory terr3("Pointe-Claire", map5.getContinent("Dorval"), 0, 1, {"Kirkland"});

    *terr1=terr3;
    map5.addTerritory(terr1);
    map5.getContinent("Dorval")->addTerritory(map5.getTerritory("Pointe-Claire"));

    map5.initAdjMatrix();
    vector<string>adjTerrName;
    for (Continent* c:map5.getContinents()){
        c->initAdjMatrix();
        for (Territory* t:c->getTerritories()){
            adjTerrName.push_back(t->getName());
            for (const string& name:t->getAdjTerritoriesNames()){
                Territory* terr=map5.getTerritory(name);
                if (terr!=nullptr&&terr->getContinent()==c&&!c->isConnected(t,map5.getTerritory(name))){                 //3 checks: 1. is the destination territory pointer null 2. is the destination territory in the same continent as its source
                    c->setVertice(t,map5.getTerritory(name));                                                            //3. was the vertice between the 2 territories already created
                }
            }
        }
    }
    adjTerrName.clear();
    //populate the adjacency matrix for the map
    for (Territory* t:map5.getTerritories()){
        adjTerrName.push_back(t->getName());
        for (const string& name:t->getAdjTerritoriesNames()){
            Territory* terr=map5.getTerritory(name);
            if (terr!=nullptr&&!map5.isConnected(t,map5.getTerritory(name))){
                map5.setVertice(t,map5.getTerritory(name));
            }
        }
    }

    if (map5.validate()){
        cout<<std::endl<<"Map "<<map5.getName()<<" was validated and will now be printed below!"<<std::endl<<std::endl<<map5<<endl;
    }

    cout<<"Here is example of a stream insertion for a continent : "<<endl<<endl<<*map5.getContinent("Dorval")<<endl;

    cout<<"Here is example of a stream insertion for a territory : "<<endl<<endl<<*map5.getTerritory("Kirkland")<<endl;

    cout<<"Here is example of a stream insertion for a map loader : "<<endl<<endl<<mapLoader<<endl;

    delete continent1;
    delete terr1;
}

// int main()
// {
//     testLoadMap();
// }