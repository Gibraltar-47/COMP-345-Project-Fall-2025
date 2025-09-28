//
// Created by Malak on 2025-09-27.
//

#include "Map.h"
#include <vector>
#include <string>
#include <iostream>
using std::string;
using std::vector;
using std::cout;

class Map {

        //private attributes by default of the class Map
        string name;
        vector<Territory*> territories; //collection of all the territories that are in the map, according to requirements, a map has a maximum of 255 territories
        vector<Continent*> continents; //collection of all the continents that are in the map, according to requirements, a map has a maximum of 32 continents
        vector<vector <int>> adjMatrix; //this reperesents a matrix of all vertices connected to all nodes in the map (the index in the adjMatrix represents the the index of the corresponding Territory instance in the vector of territories)

        public:
        //constructor with a string name parameter
        Map(string n):name(n) {}

        //copy constructor of another Map instance
        Map(const Map& otherMap){
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
        ~Map(){
            
            for(Territory* t : territories){
                delete t;
            }

            for(Continent* c : continents){
                delete c;
            }

        }

        //getter for the name attribute
        string getName(){
            return name;
        }

        //setter for the name attribute
        void setName(string n){
            name = n;
        }

        //getter for the collection of the territories attribute
        vector <Territory*> getTerritories(){
            return territories;
        }

        //setter for a territory instance in the collection
        void setTerritories(int index, Territory* t){
            territories[index]= new Territory(*t);
        }

        //getter for the collection of the continents attribute
        vector <Continent*> getContinents(){
            return continents;
        }

        //setter for a territory instance in the collection
        void setContinents(int index, Continent* c){
            continents[index]= new Continent(*c)    ;
        }

        //adding Territory instances to the vector territories
        //NOTE: in this method, a deep copy is used because there is a full aggregation association between the map and its territories
        void addTerritory(Territory* t){
            territories.push_back(new Territory(*t));
        }

        //adding Continent instances to the vector continents
        //NOTE: in this method, a deep copy is used because there is a full aggregation association between the map and its continents
        void addContinent(Continent* c){
            continents.push_back(new Continent(*c));
        }

        //getter for boolean value if there is vertice in the adjacency matrix between 2 territories
        bool isConnected(Territory* t1, Territory* t2){
            
            //the index of a vector cannot be -1 so if these variables are still -1 after the for loop, then t1 and t2 were not found in the territories vector
            int t1Index, t2Index;
            t1Index=-1;
            t2Index=-1;

            for (int i=0; i<territories.size(); i++)
            {
                if(territories[i]==t1){
                    t1Index=i;
                } else if (territories[i]==t2){
                    t2Index=i;
                }
            }

            if (t1Index==-1||t2Index==-1){
                cout<<"Either "<<t1<<" or "<<t2<<" is not in this map";
                return false;
            }

            if (adjMatrix[t1Index][t2Index]==1){
                return true;
            } else if (adjMatrix[t1Index][t2Index]==0){
                return false;
            } else {
                cout<<"Invalid input in the adjacency matrix of map "<<name;
            }
        
        }

        //setter for vertices in adjMatrix
        void setVertice(Territory* t1, Territory* t2){
            //the index of a vector cannot be -1 so if these variables are still -1 after the for loop, then t1 and t2 were not found in the territories vector
            int t1Index, t2Index;
            t1Index=-1;
            t2Index=-1;

            for (int i=0; i<territories.size(); i++)
            {
                if(territories[i]==t1){
                    t1Index=i;
                } else if (territories[i]==t2){
                    t2Index=i;
                }
            }

            if (t1Index==-1||t2Index==-1){
                cout<<"Either "<<t1<<" or "<<t2<<" is not in this map";
            }

            adjMatrix[t1Index][t2Index]=1;
            adjMatrix[t2Index][t1Index]=1; //because the graph is undirected
        }
};

class Continent{};

class Territory{
    string name;
    Continent* continent; //each territory belongs to exactly one continent
    Player* owner; //each territory is owned by exactly one player
    int numOfArmies; //number of armies in the territory
    int x; //x coordinate of the territory on the map
    int y; //y coordinate of the territory on the map
    vector <string> adjacentTerritoriesNames; //collection of the names of all the territories that are adjacent to this territory

    public:
    //constructor
    Territory(string n, Continent* c, int x_coord, int y_coord, vector <string> adjT):name(n),continent(c), owner(nullptr), numOfArmies(0),
          x(x_coord), y(y_coord), adjacentTerritoriesNames(adjT) {}

    //copy constructor
    Territory(const Territory& otherTerr){
        this->name=otherTerr.name;
        this->numOfArmies=otherTerr.numOfArmies;
        this->x=otherTerr.x;
        this->y=otherTerr.y;
        this->adjacentTerritoriesNames=otherTerr.adjacentTerritoriesNames;

        //because the association between the owner and territories is a one-to-many, the responsability of deleting the owner should be on the owner
        //for the continent, we already assumed the responsability of the lifetime of the continents to the class Map, therefore, Territory should only do a shallow copy of its continent as well as the owner
        this->owner=otherTerr.owner;
        this->continent=otherTerr.continent;
    }
};