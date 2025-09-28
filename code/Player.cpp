//
// Created by ngyna on 2025-09-26.
//

#include "Player.h"
#include <iostream>
//default constructor
Player::Player(): name("Unknown"), territories(), handCards(), orders(){

}
//cons with name
Player::Player(const std:: string& playerName){
   name=playerName;

}
//copy constructor
Player::Player(const Player& other): name(other.name), territories(other.territories), handCards(other.handCards){
//deep copy
for(Order* o:other.orders){
 orders.push_back(new Order(*o));
  }
}
//destructor
 Player::~Player(){
 //clean up dynamically allocated orders
 for(Order* o:orders){
delete o;
}
orders.clear();
 }
//getters and setters
 std::string Player::getName() const{
  return name;
}
void Player::setName(const std::string& newName){
   name=newName;
}
//methods
   void Player::addTerritory(Territory* tr) {
    if (tr != nullptr) {
        territories.push_back(tr);
    }
}
   void Player::addCard(Card* ca) {
   if(ca!=nullptr){
  handCards.push_back(ca);
 }
}
    void Player::addOrder(Order* ord) {
    if(ord!=nullptr){
     orders.push_back(ord);
      }
}
 std::vector<Territory*> Player::toDefend() const{
    return territories;
}
 std::vector<Territory*> Player::toAttack() const {
 std::vector<Territory*> attackList;
  return attackList;
}
 void Player::issueOrder(){
  std::cout<<name<<" issuing orders "<<std::endl;
 for(Order* o: orders){
 std::cout<<o->getResult()<<" ";

}
 std::cout<<std::endl;
 orders.clear();
}
  void Player::printStatus() const{
 std::cout<<"Player: "<<name<<std::endl;
  std::cout<<"Territories: ";
  for(Territory* t:territories){
   std::cout<<t->getName()<<" ";
}
 std::cout<<std::endl;
 std::cout<<"Hand Card: ";
 for(Card* c:handCards){
std::cout<<c->getType()<< " ";
}
 std::cout <<std::endl;
 std::cout<<"Orders: ";
 for(Order* o: orders){
 std::cout<<o->getResult()<< " ";
}
 std:: cout<<std::endl;
}
 const std:: vector<Order*> Player::getOrderList() const{
return orders;
}

