#include "Player.h"
// #include "Territory.h"
// #include "Cards.h"
#include "../Orders/Orders.h"
#include "../part1-map/Map.h"
#include "../Part-4-Deck/Cards.h"

#include <iostream>
#include <algorithm>
using namespace std;

// Territory::Territory() : name("Unknown Territory"), owner(nullptr) {}
// Territory::Territory(std::string name, Player* owner) : name(name), owner(owner) {}
// std::string Territory::getName() {return this->name;}
// Player* Territory::getOwner() {return this->owner;}
// void Territory::setOwner(Player* owner) {this->owner = owner;}

// Cards::Cards() : name("Unknwon Card") {}
// std::string Cards::getName() {return this->name;}



Player::Player() : name("hi") {
    orderList=new OrdersList();
}

//cons with name
Player::Player(const std:: string& playerName): name(playerName), territories(), handCards() {
    orderList=new OrdersList();
}

Player::Player(const Player& other){
    name=other.name;

    //shallow copy terr and handcards
    territories=other.territories;
    handCards= other.handCards;

    //orders.clear();

    orderList=new OrdersList(*other.orderList); //deep copy
}

//asignment operator
Player& Player::operator=(const Player& other){
    if(this!=&other){
        name=other.name;
        territories=other.territories;
        handCards=other.handCards;

        //deep copy the new list
        orderList =new OrdersList(*other.orderList);
    }
    return *this;
}

Player::~Player(){
    delete orderList; //delete the Orderlist
}

//stream insertion operator
// ostream& operator<<(std::ostream& out, const Player& p){
//     out<<"Player: "<<p.name<<"\n";
//     out<<"Territories: ";
//     if(!p.territories.empty()){
//         for(auto t:(p.territories))
//             out<< t->getName()<<" ";
//     } 
//     else out<<"none";
//     out<<"\n";

//     out<<"Hand: ";
//     if(!p.handCards.empty()){
//         for(auto c: p.handCards)
//             out<<c->getName()<<" ";
//     } 
//     else{
//             out<<"none";
//     }
//     out<<"\n";

//     out<<"Orders: ";
//     out<<"none\n";
//     return out;
// }

//getters and setters
 string Player::getName() const{
  return name;
}
void Player::setName(const string& newName){
   name=newName;
}
std::vector<Territory*> Player::getTerritories() {
    return this->territories;
}

OrdersList* Player::getOrderList(){
    return this->orderList;
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
    if (ca!=nullptr){
        handCards.push_back(ca);
        cout<<name<<" has card: "<<ca->getName()<<endl;
   }
}

//add an order to the player's order list. Player owns the order list and it will delete it in the destructor
void Player::addOrder(Orders* ord) {
    orderList->add(ord);
}

//execute all the orders in rderList, prints the result, deletes each order after execution and clear the vector
void Player::issueOrder(){
    // auto list=orderList->getList();
    // if(list.empty()){
    //     cout<<name<<" has no orders to issue."<<endl;
    //     return;
    // }

    // cout<<name<<" has these issues to order: "<<endl;

    // for(Orders* o: list){
    //     if(o){
    //         o->execute();
    //         cout<<*o<<endl;
    //     }
    // }
    // orderList->setList();


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
vector<Territory*> Player::toAttack(const std::vector<Territory*>& allTerritories) const {
    std::vector<Territory*> attackList;

    cout << "TO ATTACK FUNCTION" << endl;

    // // Loop through each territory the player owns
    // for (Territory* myTerritory : territories) {
    //     if (!myTerritory) continue;

    //     // Loop through adjacent territory names
    //     for (const std::string& adjName : myTerritory->getAdjTerritoriesNames()) {
    //         // Find the Territory object by name in allTerritories
    //         auto it = std::find_if(allTerritories.begin(), allTerritories.end(),[&](Territory* t) {
    //             return t && t->getName() == adjName && t->getOwner() != this;
    //         });

    //         // If found and not already in attackList, add it
    //         if (it != allTerritories.end() && std::find(attackList.begin(), attackList.end(), *it) == attackList.end()) {
    //             attackList.push_back(*it);
    //         }
    //     }
    // }
 return attackList;
}

 //print the status of the player
 void Player::printStatus() const{
    cout << "PLAYER PRINT STATUS" << endl;


//   cout<<"Player: "<<name<<endl;
//   cout<<"Territories: ";
//   if(territories.empty()) cout<<"none";
//   else for(Territory* t: territories) cout<<t->getName()<<" ";
//   cout<<"\n Hand cards: ";
//   if(handCards.empty()) cout<<"none";
//   else for(Card* c: handCards) cout<<c->getName()<<" ";
//   cout<<endl;
//   cout<<"Orders: ";
//   const auto list=orderList->getList();
//   if(list.empty()) cout<<"none";
//   else for (Orders* o:list) cout<< o->getName();
//   cout<<endl;
 }

bool Player::equals(Player* player2){
    if (this->name != player2->name)
        return false;
    
    if (this->territories.size() != player2->territories.size())
        return false;

    for (int n = 0; n < this->territories.size(); n++){
        if (!(this->territories[n] == player2->territories[n]))
            return false;
    }
    return true;
}