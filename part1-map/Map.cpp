//
// Created by Malak on 2025-09-27.
//

#include "Map.h"
#include <vector>
using std::vector;
#include <string>
using std::string;
#include <iostream>
using std::ostream;
using std::cout;


//forward declaration
class Territory;
class Continent;

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

//copy assignment operator
Map& Map::operator = (const Map& otherMap){
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

//adding Territory instances to the vector territories
//NOTE: in this method, a deep copy is used because there is a full aggregation association between the map and its territories
void Map::addTerritory(Territory* t){
    territories.push_back(new Territory(*t));
    int n = territories.size();
    adjMatrix.resize(n ,vector<int>(n,0));//create a column for the vertices connected to the new territory
}

//adding Continent instances to the vector continents
//NOTE: in this method, a deep copy is used because there is a full aggregation association between the map and its continents
void Map::addContinent(Continent* c){
    continents.push_back(new Continent(*c));
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

ostream& operator <<(ostream& out, const Map& map){
    out<<"Map name: "<<map.name<<"\n";
    out<<"Here are the continents and their respective territorries in the map : \n";
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

Continent::Continent(string n, int p):name(n),pointsToConquer(p){}

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

void Continent::setName(string n){
    name=n;
}

int Continent::getPointsToConquer(){
    return pointsToConquer;
}

void Continent::setPointsToConquer(int p){
    pointsToConquer=p;
}

void Continent::addTerritory(Territory* t){
    territories.push_back(t);
}

vector<Territory*> Continent::getTerritories(){
    return territories;
}

bool Continent::isConnected(Territory* t1, Territory* t2){
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
        cout<<"Either "<<(t1 ? t1->getName() : "null")<<" or "<<(t2 ? t2->getName() : "null")<<" is not in this continent";
    }

    adjMatrix[t1Index][t2Index]=1;
    adjMatrix[t2Index][t1Index]=1; //because the graph is undirected
}

//constructor
Territory::Territory(string n, Continent* c, int x_coord, int y_coord, vector <string> adjT):
    name(n),
    continent(c), 
    numOfArmies(0),
    x(x_coord), 
    y(y_coord), 
    adjTerritoriesNames(adjT), 
    owner(nullptr) 
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

int Territory::getNumOfArmies(){
    return numOfArmies;
}

void Territory::setNumOfArmies(int num){
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
void Territory::addAdjTerritoriesNames(string name){
    adjTerritoriesNames.push_back(name);
}

int main() {
    Continent* Europe = new Continent("Europe", 5);
    Continent* EuropeCopy = new Continent(*Europe);

    Territory* France = new Territory("France", Europe, 100, 200, {"Germany", "Italy"});
    Territory* Germany = new Territory("Germany", Europe, 150, 250, {"France", "Italy"});
    Territory* Italy = new Territory("Italy", Europe, 200, 300, {"France", "Germany"});
    Territory* FranceCopy = new Territory(*France);

    Map* map1 = new Map("World Map");
    map1->addContinent(Europe);
    map1->addTerritory(France);
    map1->addTerritory(Germany);
    map1->addTerritory(Italy);
    map1->getContinents()[0]->addTerritory(France);
    map1->getContinents()[0]->addTerritory(Germany);
    map1->getContinents()[0]->addTerritory(Italy);
    map1->setVertice(France, Germany);
    map1->setVertice(France, Italy);
    map1->setVertice(Germany, Italy);

    cout<<*map1;

    if (map1->isConnected(France,Italy))
    {
        cout<<"France and Italy are connected";
    }

    delete Europe;
    delete EuropeCopy;
    delete France;
    delete FranceCopy;
    delete Germany;
    delete Italy;
    delete map1;
    return 0;
}