//
// Created by ngyna on 2025-09-26.
//

#include "player.h"
#include <iostream>

Player::Player(){
    name = "Unknown";
   territories=std::vector<Territory*>();
    hand=std::vector<Card*>();
    orders=std::vector<Order*>();
}
Player::Player(const std:: string& playerName){
   name=playerName;

}
 std::string Player::getName() const{
  return name;
}
void Player::setName(const std::string& newName){
   name=newName;
}
   void Player::addTerritory(Territory* tr) {
    if (tr != nullptr) {
        territories.push_back(tr);
    }
}
   void Player::addCard(Card* cr) {
   if(cr!=nullptr){
  hand.push_back(cr);
 }
}
    void Player::addOrder(Order* ord) {
    if(ord!=nullptr){
     orders.push_back(ord);
      }
}
 std::vector<Territory*> Player::toDefend(){
    return territories;
}
 std::vector<Territory*> Player::toAttack(){
 std::vector<Territory*> attackList;
  return attackList;
}
 void Player::issueOrder(){
  Order* newOrder=new Order();
  orders.push_back(newOrder);
}
