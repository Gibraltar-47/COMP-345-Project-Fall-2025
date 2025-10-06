//
// Created by ngyna on 2025-09-26.
//

#include "Player.h"
#include <iostream>
#include <algorithm>
using namespace std;
//default constructor, initializes name unknown, empty vectors for territories, cards and orders
Player::Player(): name("Unknown"), territories(), handCards(){
orderList=new OrdersList(); //dynamically allocates orderlist

}
//cons with name
Player::Player(const std:: string& playerName):name(playerName){
   orderList=new OrdersList();

}
/*copy constructor, creates a new player object as a copy of another plyer, deep copy the orders but shallow copy the
territories and handcards because Player owns the orders and is responsible for creating and destroying the Order
objects, shallow copy the territories and handcars because player does not own them and if we deep copy them it would
create duplicate terr and cards (Two different objects cannot be representing the same terr or card)*/
Player::Player(const Player& other){
name=other.name;
//shallow copy terr and handcards
territories=other.territories;
handCards= other.handCards;
orderList=new OrdersList(*other.orderList); //deep copy
}

//looping through the orders vector of other player
  for(Order* o : other.orders){
/*calling the copy constructor of Order class, creating a new Order obj in memory, it ensures we don't just copy
the pointer, we create a seperate obj
*/
    orders.push_back(new Order(*o));
  }
}
//aasignment operator
 Player& Player::operator=(const Player& other){
  if(this!=&other){
 name=other.name;
 territories=other.territories;
 handCards=other.handCards;
//delete old orders
 for(*Order o:orders){
delete o;
orders.clear();
 }
//copy new ones
 for(Order* o:other.orders){
orders.push_back(new Order(*o));
}
delete orderList;
//deep copy the new list
orderList =new OrdersList(*other.orderList);
}
 return *this;

}

/*destructor, cleans up dynamically allocated orders(player owns them), but doesn't delete Territories and Cards cause
player has no ownership*/
 Player::~Player(){
 delete orderList; //delete the Orderlist

 }
//stream insertion operator
std:: ostream& operator<<(std::ostream& out, const Player& p){
  out<<"Player: "<<p.name<<"\n";
 out<<"Territories: ";
  if(p.territories && !p.territories->empty()){
 for(auto t:(p.territories))
  out<< t->getName()<<" ";
} else out<<"none";
 out<<"\n";
 out<<"Hand: ";
 if(p.hand&& !p.hand->getCards().empty()){
for(auto c: p.hand->getCards())
out<<c->getName()<<" ";
} else out<<"none";
 out<<"\n";
 out<<"Orders:";
 if(p.orderList&& !p.orderList->getOrders().empty()){
 for(auto o: p.orderList->getOrders())
 out<<o->getName()<<" ";

} else out<<"none";
out<<"\n";
return out;


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
 auto list=orderList->getList();
   if(list.empty()){
   cout<<name<<" has no orders to issue."<<endl;
   return;
 }
    cout<<name<<" has these issues to order: "<<endl;
 for(Order* o: list){
 if(o){
o->execute();
cout<<*o<<endl;
}
}
orderList->setList();
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
//check if it's not already in the list
   if(find(attackList.begin(), attackList.end(),*it)==attackList.end()){

              attackList.push_back(*it);
         }
       }
    }

 return attackList;
}
//print the status of the player
  void Player::printStatus() const{
 cout<<"Player: "<<name<<endl;
  cout<<"Territories: ";
    if(territories.empty()) cout<<"none";
   else for(Territory* t: territories) cout<<t->getName()<<" ";
 cout<<endl;
cout<<"Hand cards: ";
if(handCards.empty()) cout<<"none";
else for(Card* c: handCards) cout<<c->getName()<<" ";
cout<<endl;
cout<<"Orders: ";
if(orderList->getList().empty()) cout<<"none";
else cout<<*orderList;
cout<<endl;
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



