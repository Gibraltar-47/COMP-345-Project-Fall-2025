//
// Created by Malak on 2025-09-27.
//

#include <iostream>
#include <set>
#include <string>
#include <vector>
#include "Map.h"
#include <sstream>
using std::vector;
using std::string;
using std::ostream;
using std::cout;
using std::set;
using std::ifstream;


//forward declaration
class Territory;
class Continent;

//free functions needed for Map::validate()
void recursDFS(vector <vector<int>> &adjM,vector<bool> &visited,int n){
    visited[n] = true;

    for (int i=0;i<adjM[n].size();i++){
        if (!visited[i]&&adjM[n][i]==1){
            recursDFS(adjM, visited, i);
        }
    }
}

void isConnectedGraph(vector <vector<int>> &adjM, string n, string type){
    vector<bool> visited(adjM.size(), false);
    recursDFS(adjM, visited, 0);
    for (bool b : visited){
        if (!b){
            cout<<type<<" "<<n<<" is not a connected graph"<<"\n";
            return;
        }
    }
    cout<<type<<" "<<n<<" is a connected graph"<<"\n";
}

//constructor with a string name parameter
Map::Map(string n):name(n){}

//copy constructor of another Map instance
Map::Map(const Map& otherMap){
    this->name = otherMap.name;

    for (Territory* t: otherMap.territories) {
        this->territories.push_back(new Territory(*t));
    }

    for (Continent* c: otherMap.continents) {
        this->continents.push_back(new Continent(*c));
    }

    this->adjMatrix = otherMap.adjMatrix;
}

//comparing method

//copy assignment operator
Map& Map::operator = (const Map& otherMap){
    //check if this and otherMap are the same
    this->name = (otherMap.name);

    //delete the current territories and continents to avoid memory leaks
    for(Territory* t : territories){
        delete t;
    }
    territories.clear();

    for(Continent* c : continents){
        delete c;
    }
    continents.clear();

    for (Territory* t: otherMap.territories) {
        this->territories.push_back(new Territory(*t));
    }

    for (Continent* c: otherMap.continents) {
        this->continents.push_back(new Continent(*c));
    }

    this->adjMatrix = otherMap.adjMatrix;

    return *this;
}

//destructor because Map has attribute that are of user-defined class type (territories and continents)
Map::~Map(){
    
    for(Territory* t : territories){
        delete t;
    }

    for(Continent* c : continents){
        delete c;
    }
//clear vectors
}

//getter for the name attribute
string Map::getName(){
    return name;
}

//setter for the name attribute
void Map::setName(string n){
    name = n;
}

//getter for the collection of the territories attribute
vector <Territory*> Map::getTerritories(){
    return territories;
}

//getter for the collection of the continents attribute
vector <Continent*> Map::getContinents(){
    return continents;
}

vector<vector<int>> Map::getAdjMat(){
    return adjMatrix;
}

//adding Territory instances to the vector territories
//NOTE: in this method, a deep copy is used because there is a full aggregation association between the map and its territories
void Map::addTerritory(Territory* t){
    territories.push_back(new Territory(*t));
}

//adding Continent instances to the vector continents
//NOTE: in this method, a deep copy is used because there is a full aggregation association between the map and its continents
void Map::addContinent(Continent* c){
    continents.push_back(new Continent(*c));
}

Continent* Map::getContinent(const string& n){
    for (Continent* c:continents){
        if (c->getName()==n){
            return c;
        }
    }
    return nullptr;
}

//getter for boolean value if there is vertice in the adjacency matrix between 2 territories
bool Map::isConnected(Territory* t1, Territory* t2){
    
    //the index of a vector cannot be -1 so if these variables are still -1 after the for loop, then t1 and t2 were not found in the territories vector
    int t1Index, t2Index;
    t1Index=-1;
    t2Index=-1;

    for (int i=0; i<territories.size(); i++)
    {
        if(*territories[i]==*t1){
            t1Index=i;
        } else if (*territories[i]==*t2){
            t2Index=i;
        }
    }

    if (t1Index==-1||t2Index==-1){
        cout<<"Either "<<(t1 ? t1->getName() : "null")<<" or "<<(t2 ? t2->getName() : "null")<<" is not in this map";
        return false;
    }

    if (adjMatrix[t1Index][t2Index]==1){
        return true;
    } else if (adjMatrix[t1Index][t2Index]==0){
        return false;
    } else {
        cout<<"Invalid input in the adjacency matrix of map "<<name;
        return false;
    }

}
//initialize the size of the matrix
void Map::initAdjMatrix(){
    int size=territories.size();
    adjMatrix.resize(size,vector<int> (size, 0));
}

//setter for vertices in adjMatrix
void Map::setVertice(Territory* t1, Territory* t2){
    //the index of a vector cannot be -1 so if these variables are still -1 after the for loop, then t1 and t2 were not found in the territories vector
    int t1Index, t2Index;
    t1Index=-1;
    t2Index=-1;

    for (int i=0; i<territories.size(); i++)
    {
        if(*territories[i]==*t1){
            t1Index=i;
        } else if (*territories[i]==*t2){
            t2Index=i;
        }
    }

    if (t1Index==-1||t2Index==-1){
        cout<<"Either "<<(t1 ? t1->getName() : "null")<<" or "<<(t2 ? t2->getName() : "null")<<" is not in this map";
        return;
    }

    adjMatrix[t1Index][t2Index]=1;
    adjMatrix[t2Index][t1Index]=1; //because the graph is undirected
}

void Map::validate()
{
    //1. verify that the map is a connected graph through DFS function isConnectedGraph
    isConnectedGraph(adjMatrix,name,"Map");

    //2. verify that the country is a connected graph through DFS function isConnectedGraph
    isConnectedGraph(adjMatrix,continents[0]->getName(),"Continent");

    //3.1 check if any territory is being repeated in any continent's territories list
    set <Territory*> setTerr;
    for (Continent* c: continents){
        for (Territory* t: c->getTerritories()){
            if (setTerr.count(t)){
                cout<<t->getName()<<" appears in more than one continent"<<std::endl;
                return;
            }else{setTerr.insert(t);}
        }
    }
    //3.2 check if every territory has an association to a continent or nullptr
    for (Territory* t: territories){
        if (t->getContinent()==nullptr){
            cout<<t->getName()<<" is not associated to any continent"<<std::endl;
            return;
        }
    }

    cout<<"All the territories in "<<name<<" belong to one and exactly one territory!"<<std::endl;
}

ostream& operator <<(ostream& out, const Map& map){
    out<<"Map name: "<<map.name<<"\n";
    out<<"Here are the continents and their respective territories in the map : \n";
    for(Continent* c: map.continents){
        out<<"\t-\t"<<c->getName()<<"\n";
        for(Territory* t: c->getTerritories()){
            out<<"\t\t-\t"<<t->getName()<<" is connected to\n";
            for (string name: t->getAdjTerritoriesNames()){
                out<<"\t\t\t-\t"<<name<<"\n";
            }
        }
    }
    return out;
}

Continent::Continent(const string& n, const int p):name(n),pointsToConquer(p){}

//copy constructor, NOTE: because only MAP will be accessed (and has deep copies of both continents and territories), 
//there is no need to make a deep copy of territories (the map object can access it directly through its deep copy)
Continent::Continent(const Continent& otherContinent){
    this->name=otherContinent.name;
    this->pointsToConquer=otherContinent.pointsToConquer;
    this->adjMatrix=otherContinent.adjMatrix;
    this->territories=otherContinent.territories;
}

Continent& Continent::operator =(const Continent& otherContinent){
    this->name=otherContinent.name;
    this->pointsToConquer=otherContinent.pointsToConquer;
    this->adjMatrix=otherContinent.adjMatrix;
    this->territories=otherContinent.territories;

    return *this;
}

Continent::~Continent(){
    //no deep copy, therefore the destructor contains nothing
}

string Continent::getName(){
    return name;
}

void Continent::setName(const string& n){
    name=n;
}

int Continent::getPointsToConquer(){
    return pointsToConquer;
}

void Continent::setPointsToConquer(const int p){
    pointsToConquer=p;
}

void Continent::addTerritory(Territory* t){
    territories.push_back(t);
}

vector<Territory*> Continent::getTerritories(){
    return territories;
}

bool Continent::isConnected(Territory* t1, Territory* t2) {
    int t1Index = -1;
        int t2Index = -1;

        for (int i=0; i<territories.size(); i++)
        {
            if(*territories[i]==*t1){
                t1Index=i;
            } else if (*territories[i]==*t2){
                t2Index=i;
            }
        }

        if (t1Index==-1||t2Index==-1){
            cout<<"Either "<<(t1 ? t1->getName() : "null")<<" or "<<(t2 ? t2->getName() : "null")<<" is not in this continent";
            return false;
        }

        if (adjMatrix[t1Index][t2Index]==1){
            return true;
        } else if (adjMatrix[t1Index][t2Index]==0){
            return false;
        } else {
            cout<<"Invalid input in the adjacency matrix of continent "<<name;
            return false;
        }
}

//setter for vertices in adjMatrix
void Continent::setVertice(Territory* t1, Territory* t2){
    int t1Index = -1;
    int t2Index = -1;

    for (int i=0; i<territories.size(); i++)
    {
        if(*territories[i]==*t1){
            t1Index=i;
        } else if (*territories[i]==*t2){
            t2Index=i;
        }
    }

    if (t1Index==-1||t2Index==-1){
        cout<<"Either "<<(t1 ? t1->getName() : "null")<<" or "<<(t2 ? t2->getName() : "null")<<" is not in this continent";
    }

    adjMatrix[t1Index][t2Index]=1;
    adjMatrix[t2Index][t1Index]=1; //because the graph is undirected
}
//initialize the size of the matrix
void Continent::initAdjMatrix(){
    const int size=territories.size();
    adjMatrix.resize(size,vector<int> (size, 0));
}

//constructor
Territory::Territory(const string& n, Continent* c, const int x_coord, const int y_coord, const vector <string>& adjT):
    name(n),
    continent(c), 
    owner(nullptr),
    numOfArmies(0),
    x(x_coord),
    y(y_coord),
    adjTerritoriesNames(adjT)
{}

//copy constructor
Territory::Territory(const Territory& otherTerr){
    this->name=otherTerr.name;
    this->continent=otherTerr.continent;
    this->owner=otherTerr.owner;
    this->numOfArmies=otherTerr.numOfArmies;
    this->x=otherTerr.x;
    this->y=otherTerr.y;
    this->adjTerritoriesNames=otherTerr.adjTerritoriesNames;
}

//copy assignment operator
Territory& Territory::operator = (const Territory& otherTerr){
    this->name=otherTerr.name;
    this->continent=otherTerr.continent;
    this->owner=otherTerr.owner;
    this->numOfArmies=otherTerr.numOfArmies;
    this->x=otherTerr.x;
    this->y=otherTerr.y;
    this->adjTerritoriesNames=otherTerr.adjTerritoriesNames;

    return *this;
}

//destructor
Territory::~Territory(){
    //nothing in destructor because there is no deep copy in the construction of a Territory
}

//comparing operator to make comparison through ==
bool Territory::operator ==(const Territory& otherTerr){
    return this->name==otherTerr.name;
}

//accessors & mutators
string Territory::getName(){
    return name;
}

void Territory::setName(string n){
    name=n;
}

Continent* Territory::getContinent(){
    return continent;
}

void Territory::setContinent(Continent* c){
    continent=c;
}

Player* Territory::getOwner(){
    return owner;
}

void Territory::setOwner(Player* p){
    owner=p;
}

int Territory::getNumOfArmies() {
    return numOfArmies;
}

void Territory::setNumOfArmies(const int num){
    numOfArmies=num;
}

vector<string> Territory::getAdjTerritoriesNames(){
    return adjTerritoriesNames;
}
//a method to replace the entire list
void Territory::setAdjTerritoriesNames(vector <string> list){
    adjTerritoriesNames=list;
}
//a method to add a single name
void Territory::addAdjTerritoriesNames(const string& n){
    adjTerritoriesNames.push_back(n);
}
MapLoader::MapLoader(){}; //no private member to initialize
MapLoader::MapLoader(const MapLoader& otherMapLoader){};
MapLoader::~MapLoader(){}
MapLoader& MapLoader::operator = (const MapLoader& otherMapLoader){return *this;};//there is no difference between a MapLoader to another

void MapLoader::loadMap(const string& filename){
    inputFileStream.open(filename);
    if (inputFileStream.is_open()){

       string line,mapName="",conName="",terrName="";
       int firstPos=-1, secondPos=-1,step=0,x,y,p;
       vector <string> adjTerrName,terrInfo;
       Map map1("holder");
       Continent* conHolder = new Continent("holder", 0);
       Territory terrHolder(terrName,conHolder,x,y,adjTerrName);

       while(getline(inputFileStream,line)){
            if (line=="[Map]"){
                getline(inputFileStream, line);
                firstPos=line.find("=");
                secondPos=line.find(".");
                mapName=line.substr(firstPos+1,secondPos-firstPos-1);
                Map map1(mapName);
                cout<<mapName<<std::endl;
                step++;
                continue;
            }
           if (step==1){
                if (line=="[Continents]"){
                    getline(inputFileStream, line);
                    firstPos=line.find("=");
                    conName=line.substr(0,firstPos);
                    p=stoi(line.substr(firstPos+1,line.size()-firstPos-1));
                    map1.addContinent(new Continent(conName,p));
                    cout<<conName<<" "<<p<<std::endl;
                }else if (line=="[Territories]"){
                    step++;continue;
                }
           }
           if (step==2){
               std::stringstream terrInfoStream(line);
               while (getline(terrInfoStream,terrName,',')){
                   terrInfo.push_back(terrName);
               }
               for (int i=0;i<terrInfo.size();i++){
                   if (i==0){
                       terrName=terrInfo[0];
                   }else if (i==1){
                       x=stoi(terrInfo[1]);
                   }else if (i==2){
                       y=stoi(terrInfo[2]);
                   }else if (i==3){
                       conName=terrInfo[3];
                       conHolder=map1.getContinent(conName);
                   }else if (i>3){
                       adjTerrName.push_back(terrInfo[4]);
                   }
               }
               map1.addTerritory(new Territory(terrName,conHolder,x,y,adjTerrName));
               break;
           }
       }
    }
    inputFileStream.close();
};

ostream& operator << (ostream& out, const MapLoader& mapLoader);

int main() {
    // const auto Europe = new Continent("Europe", 5);
    // const auto EuropeCopy = new Continent(*Europe);
    //
    // const auto France = new Territory("France", Europe, 100, 200, {"Germany", "Italy"});
    // const auto Germany = new Territory("Germany", Europe, 150, 250, {"France", "Italy"});
    // const auto Italy = new Territory("Italy", Europe, 200, 300, {"France", "Germany"});
    // const auto FranceCopy = new Territory(*France);
    //
    // const auto map1 = new Map("World Map");
    // map1->addContinent(Europe);
    // map1->addTerritory(France);
    // map1->addTerritory(Germany);
    // map1->addTerritory(Italy);
    // map1->getContinents()[0]->addTerritory(France);
    // map1->getContinents()[0]->addTerritory(Germany);
    // map1->getContinents()[0]->addTerritory(Italy);
    //
    // map1->initAdjMatrix();
    //
    // map1->setVertice(France, Germany);
    // map1->setVertice(France, Italy);
    // map1->setVertice(Germany, Italy);
    //
    // cout<<*map1;
    // // cout<<map1->getTerritories().size()<<std::endl;
    // // cout<<map1->getAdjMat()[0].size()<<std::endl;
    //
    // if (map1->isConnected(France,Italy))
    // {
    //     cout<<"France and Italy are connected"<<std::endl;
    // }
    //
    // map1->validate();
    //
    // delete Europe;
    // delete EuropeCopy;
    // delete France;
    // delete FranceCopy;
    // delete Germany;
    // delete Italy;
    // delete map1;
    auto mapLoader=MapLoader();
    mapLoader.loadMap("Aldawin.map");
    return 0;
}