//
// Created by Malak on 2025-09-27.
//

#ifndef MAP_H 
#define MAP_H

#include <vector>
using std::vector;
#include <string>
using std::string;
#include <iostream>
using std::cout;
using std::ostream;

//forward declaration
class Territory;
class Continent;

//placeholder class
class Player {
private:
    std::string name;
public:
    Player(std::string n) : name(n) {}
    std::string getName() const { return name; }
};

class Map {
private:
    string name;
    vector<Territory*> territories; //collection of all the territories that are in the map, according to requirements, a map has a maximum of 255 territories
    vector<Continent*> continents; //collection of all the continents that are in the map, according to requirements, a map has a maximum of 32 continents
    vector<vector <int>> adjMatrix; //this reperesents a matrix of all vertices connected to all nodes in the map (the index in the adjMatrix represents the the index of the corresponding Territory instance in the vector of territories)
public:
    //constructor with a string name parameter
    Map(string n);
    //copy constructor of another Map instance
    Map(const Map& otherMap);
    //copy assignment operator
    Map& operator = (const Map& otherMap);
    //destructor because Map has attribute that are of user-defined class type (territories and continents)
    ~Map();
    //getter for the name attribute
    string getName();
    //setter for the name attribute
    void setName(string n);
    //getter for the collection of the territories attribute
    vector <Territory*> getTerritories();
    //getter for the collection of the continents attribute
    vector <Continent*> getContinents();
    //setter for a territory instance in the collection
    void setContinents(int index, Continent* c);
    //adding Territory instances to the vector territories
    //NOTE: in this method, a deep copy is used because there is a full aggregation association between the map and its territories
    void addTerritory(Territory* t);
    //adding Continent instances to the vector continents
    //NOTE: in this method, a deep copy is used because there is a full aggregation association between the map and its continents
    void addContinent(Continent* c);
    //getter for boolean value if there is vertice in the adjacency matrix between 2 territories
    bool isConnected(Territory* t1, Territory* t2);
    //setter for vertices in adjMatrix
    void setVertice(Territory* t1, Territory* t2);
    friend ostream& operator << (ostream& out, const Map& map);
};

class Continent{
private:
    string name;
    vector<Territory*> territories;
    int pointsToConquer;
    vector<vector<int>> adjMatrix;
public:
    Continent(string n, int p);
    //copy constructor, NOTE: because only MAP will be accessed (and has deep copies of both continents and territories),
    //there is no need to make a deep copy of territories (the map object can access it directly through its deep copy)
    Continent(const Continent& otherContinent);
    //copy assignment operator
    Continent& operator = (const Continent& otherContinent);
    //destructor
    ~Continent();
    //accessors
    string getName();
    int getPointsToConquer();
    vector<Territory*> getTerritories();
    bool isConnected(Territory* t1, Territory* t2);
    //mutators
    void setName(string n);
    void setPointsToConquer(int p);
    void addTerritory(Territory* t);
    //setter for vertices in adjMatrix
    void setVertice(Territory* t1, Territory* t2);
};

class Territory{
private:
    string name;
    Continent* continent;
    Player* owner;
    int numOfArmies;
    int x;
    int y;
    vector <string> adjTerritoriesNames;
public:
    //constructor
    Territory(string n, Continent* c, int x_coord, int y_coord, vector <string> adjT);
    //copy constructor
    Territory(const Territory& otherTerr);
    //copy assignment operator
    Territory& operator = (const Territory& otherTerr);
    //destructor
    ~Territory();
    //comparing operator to make comparison through ==
    bool operator ==(const Territory& otherTerr);
    //accessors
    string getName();
    Continent* getContinent();
    Player* getOwner();
    int getNumOfArmies();
    vector<string> getAdjTerritoriesNames();
    //mutators
    void setName(string n);
    void setContinent(Continent* c);
    void setOwner(Player* p);
    void setNumOfArmies(int num);
    void setAdjTerritoriesNames(vector <string> list);
    void addAdjTerritoriesNames(string name);
};

#endif