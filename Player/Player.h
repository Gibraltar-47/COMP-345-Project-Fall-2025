#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <vector>
#include <iostream>
// #include "../Orders/Orders.h"
// #include "../part1-map/Map.h"
// #include "../Part-4-Deck/Cards.h"

// Forward declarations
class Territory;
class Card;
class Orders;
class OrdersList;
class Deck;
class Hand;

using namespace std;

//forward declarations
// class Player;
// class Territory;
// class Cards;
// class Orders;
// //placeholder classes
// class OrdersList;

// class Territory {
//   private:
//     std::string name;
//     Player* owner;
  
//   public:
//     Territory();
//     Territory(std::string name, Player* owner);
//     std::string getName();
//     Player* getOwner();
//     void setOwner(Player* owner);

// };

// class Cards {
//   private:
//     std::string name;

//   public:
//     std::string getName();
// };

class Player {
  private:
    std::string name;
    std::vector<Territory*> territories; //dynamic array of territory pointers
    std::vector<Card*> handCards;
    OrdersList* orderList;


public:
   Player();
   Player(const std::string& playerName);
   Player(const Player& other); //copy constructor
   Player& operator =(const Player& other); //assignemnt operator
   ~Player(); //destructor, clears up resources when a player obj is destroyed
   std::string getName() const;
   OrdersList* getOrderList();
   std::vector<Territory*> getTerritories();
   void setName(const std::string& newName);
   void addTerritory(Territory* tr);
   void addCard(Card* ca);
   void addOrder(Orders* ord);
 //game actions
   std::vector<Territory*> toDefend() const;
   std::vector<Territory*> toAttack(const std::vector<Territory*>& allTerritories) const;
   void issueOrder(); //execute all orders and clean up memory
   void printStatus() const; //print player's name, territories
   bool equals(Player* player2);
  friend std::ostream& operator <<(std::ostream& out, const Player& p);


};

#endif