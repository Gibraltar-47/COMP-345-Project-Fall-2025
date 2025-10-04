//
// Created by ngyna on 2025-09-26.
//

#include "Player.h"
#include "Territory.h"
#include "Card.h"
#include "Order.h"
#include <iostream>
#include <algorithm>
using namespace std;
//default constructor, initializes name unknown, empty vectors for territories, cards and orders
Player::Player(): name("Unknown"), territories(), handCards(), orders(){

}
//cons with name
Player::Player(const std:: string& playerName){
   name=playerName;

}
/*copy constructor, creates a new player object as a copy of another plyer, deep copy the orders but shallow copy the
territories and handcards because Player owns the orders and is responsible for creating and destroying the Order
objects, shallow copy the territories and handcars because player does not own them and if we deep copy them it would
create duplicate terr and cards (Two different objects cannot be representing the same terr or card)*/
Player::Player(const Player& other): name(other.name), territories(other.territories), handCards(other.handCards){
  //deep copy each order
//looping through the orders vector of other player
  for(Order* o : other.orders){
/*calling the copy constructor of Order class, creating a new Order obj in memory, it ensures we don't just copy
the pointer, we create a seperate obj
*/
    orders.push_back(new Order(*o));
  }
}
/*destructor, cleans up dynamically allocated orders(player owns them), but doesn't delete Territories and Cards cause
player has no ownership*/
 Player::~Player(){
 for(Order* o:orders){
delete o; //deleting the orders
}
orders.clear(); //clearing the list
 }
//getters and setters
 string Player::getName() const{
  return name;
}
void Player::setName(const string& newName){
   name=newName;
}
//adds a terr to the player's list
void Player:: addTerritory(Territory* tr){
if(tr!=nullptr){
territories.push_back(tr);
tr->setOwner(this); //sets this player as its owner
}
}
//add a card to the player's hand and prints a string
void Player::addCard(Card* ca){
if(ca!=nullptr){
 handCards.push_back(ca);
cout<<name<<" has card: "<<ca->getName()<<endl;
   }
}
//add an order to the player's order list. Player owns the order list and it will delete it in the destructor
    void Player::addOrder(Order* ord) {
    if(ord!=nullptr){
     orders.push_back(ord);
      }
}
//return the current list of orders
const vector<Order*> Player::getOrderList() const{
 return orders;
}
//execute all the orders in rderList, prints the result, deletes each order after execution and clear the vector
 void Player::issueOrder(){
   if(orders.empty()){
   cout<<name<<" has no orders to issue."<<endl;
   return;
 }
    cout<<name<<" has these issues to order: "<<endl;
 for(Order* o: orders){
 if(o!=nullptr){
cout<<o->getResult()<<endl;
}
delete o;
}
orders.clear();
}

//returns a list of territories the player owns(to defend)
 vector<Territory*> Player::toDefend() const{
//create a new empty vector defendList to store terr
         vector<Territory*> defendList;
//loop through all the terr the player owns
 for(Territory* tr: territories){
    if(tr!=nullptr){
//add it to the list
       defendList.push_back(tr);
       }
}
return defendList;

}
//returns list of territories adjacent to player's territories but owned by other player(to attack)
 vector<Territory*> Player::toAttack(const vector<Territory*>& allTerritories) const {
 vector<Territory*> attackList; //create an empty list
 for(Territory* myTerritory: territories){ //loop through the terrs the player owns
if(myTerritory!=nullptr){
for(const string& adjName: myTerritory->getAdjTerritoriesNames()){ //for each terr, loop through the names of adj terrs
//search for Territory pointer by name
 auto it = find_if(allTerritories.begin(), allTerritories.end(), [&](Territory* t){
/*check if the territory's name matches the adj terr name, and it checks that is not owned by the current player*/
return t->getName()==adjName&& t->getOwner()!=this;

});
//checks that we found a terr matching the criteria, adj and not owned by the current player
if(it!=allTerritories.end()){
   if(find(attackList.begin(), attackList.end(),*it)==attackList.end()){
              attackList.push_back(*it);
         }
       }
    }

 return attackList;
}
//print the status of the player
  void Player::printStatus() const{
 cout<<"Player: "<<name<<std::endl;
  cout<<"Territories: ";
    if(territories.empty()){
   cout<<"(none)";

}
else{
for(Territory* t: territories){
if(t!=nullptr){
cout<<t->getName()<<" ";
}
}

cout<<endl;
cout<<"Hand Cards: ";
if(handCards.empty()){
cout<<"(none)";
} else{
for(Card* c: handCards){
if(c!=nullptr){
cout<<c->getName()<<" ";
  }
 }
cout<<endl;
cout<<"Orders: ";
if(orders.empty()){
  cout<<"(none)";
} else{
for(Order* o:orders){
if(o!=nullptr){
cout<<o->getName()<<" ";
}
}
cout<<endl;



