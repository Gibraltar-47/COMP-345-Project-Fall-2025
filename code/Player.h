//
// Created by ngyna on 2025-09-26.
//

#ifndef COMP_335_PROJECT_FALL_2025_PLAYER_H
#define COMP_335_PROJECT_FALL_2025_PLAYER_H
#include <string>
#include <vector>
#include <iostream>

class Territory;
class Card;
class Order;
class Player {
private:
   std::String name;
   std::vector<Territory*> territories; //dynamic array of pointers to Territory objs
   std::vector<Card*> handCards;
   std::vector<Order*> orders;
 //constructors, destructor, getters, setters

public:
   Player();
   Player(const std::string& playerName);
   Player(const Player& other); //copy constructor
   ~Player(); //destructor
   std::string getName() const;
   void setName(const std::string& newName);
   void addTerritory(Territory* tr);
   void addCard(Card* ca);
   void addOrder(Order* ord);
 //game actions
   std::vector<Territory*> toDefend() const;
   std::vector<Territory*> toAttack() const ;
   void issueOrder();

};


#endif //COMP_335_PROJECT_FALL_2025_PLAYER_H