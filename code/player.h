//
// Created by ngyna on 2025-09-26.
//

#ifndef COMP_335_PROJECT_FALL_2025_PLAYER_H
#define COMP_335_PROJECT_FALL_2025_PLAYER_H
#include <string>
#include <vector>

class Territory;
class Card;
class Order;
class Player {
private:
   std::string name;
   std::vector<Territory*> territories;
   std::vector<Card*> hand;
   std::vector<Order*> orders;
 // constructors, getters, setters
public:
   Player();
   Player(const std::string& playerName);
   std::string getName() const;
   void setName(const std::string& newName);
   void addTerritory(Territory* tr);
   void addCard(Card* ca);
   void addOrder(Order* ord);
   std::vector<Territory*> toDefend();
   std::vector<Territory*> toAttack();
   void issueOrder();

};


#endif //COMP_335_PROJECT_FALL_2025_PLAYER_H