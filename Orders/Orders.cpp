#include <iostream>
#include <list>
#include <algorithm>
#include <string>
#include "Orders.h"
#include "../Player/Player.h"
#include "../part1-map/Map.h"
using namespace std;

std::ostream& operator<<(std::ostream &strm, const Orders& order){
    order.printOrder(strm);
    return strm;
}
std::ostream& operator<<(std::ostream &strm, const OrdersList& orderList){
    strm << "Order List Contains the Below Orders:\n";
    for (Orders* order : orderList.getList()){
            strm << *order << endl;
       
    }
    return strm;
}
std::ostream& operator<<(std::ostream &strm, Territory& territory){
    strm << "Territory: " << territory.getName();
    return strm;
}
Orders::Orders() : issuingPlayer(nullptr) , sourceTerritory(nullptr), isActive(false), isValid(false) {}
Orders::Orders(Player* issuingPlayer, Territory* sourceTerritory) : issuingPlayer(issuingPlayer), sourceTerritory(sourceTerritory), isActive(false), isValid(false){}
Orders::Orders(const Orders& order){

    if (order.getIssuingPlayer())
        // this->issuingPlayer = new Player(*(order.issuingPlayer)); // might be fine if player class has copy constructor and assignment operator
        this->issuingPlayer = order.getIssuingPlayer();
    else   
        this->issuingPlayer = nullptr;


    if (order.getSourceTerritory())
        // this->sourceTerritory = new Territory(*(order.sourceTerritory)); // might be fine if Territory class has copy constructor and assignment operator
        this->sourceTerritory = order.sourceTerritory;
    else
        this->setSourceTerritory(nullptr);

    this->setIsActive(order.getIsActive());
    this->setIsValid(order.getIsValid());
}
Orders::~Orders(){}

Orders& Orders::operator=(const Orders& order){
    if (this != &order){
        // delete this->getSourceTerritory(); // Free old memory before assignment
        // delete this->getIssuingPlayer();

        if (order.getIssuingPlayer())
            // this->issuingPlayer = new Player(*order.issuingPlayer); // might be fine if player class has copy constructor and assignment operator
            this->issuingPlayer = order.getIssuingPlayer();
        else   
            this->issuingPlayer = nullptr;

        if (order.getSourceTerritory())
            // this->sourceTerritory = new Territory(*(order.sourceTerritory)); // might be fine if Territory class has copy constructor and assignment operator
            this->sourceTerritory = order.sourceTerritory;
        else   
            this->sourceTerritory = nullptr;
        
        this->setIsActive(order.getIsActive());
        this->setIsValid(order.getIsValid());

    }
    return *this;
}
Player* Orders::getIssuingPlayer() const{
    return this->issuingPlayer;
};
void Orders::setIssuingPlayer(Player* issuingPlayer){
    this->issuingPlayer = issuingPlayer;
}
Territory* Orders::getSourceTerritory() const{
    return this->sourceTerritory;
}
void Orders::setSourceTerritory(Territory* sourceTerritory){
    this->sourceTerritory = sourceTerritory;
}
bool Orders::getIsActive() const{
    return this->isActive;
}
void Orders::setIsActive(bool isActive){
    this->isActive = isActive;
}
bool Orders::getIsValid() const{
    return this->isValid;
}
void Orders::setIsValid(bool isValid){
    this->isValid = isValid;
}
Orders* Orders::allocateClone() const{
    return new Orders(*this);
}
void Orders::printOrder(std::ostream& strm) const{
    strm << "An Order is the superclass of all the individual orders.\nIt has no affect since it is an abstract class.";
}
bool Orders::validate(){
    cout << "Orders::validate is abstract" << endl;
    return false;

}
void Orders::execute(){
    cout << "Orders::execute is abstract" << endl;
}


OrdersDeploy::OrdersDeploy() : Orders(), numArmies(0) {}
OrdersDeploy::OrdersDeploy(Player* issuingPlayer, Territory* sourceTerritory, int numArmies) : Orders(issuingPlayer, sourceTerritory), numArmies(numArmies){}
OrdersDeploy::OrdersDeploy(const OrdersDeploy& order) : Orders(order) {
    this->setNumArmies(order.getNumArmies());
}
OrdersDeploy& OrdersDeploy::operator=(const OrdersDeploy& order){
        if (this != &order){
            Orders::operator=(order);

            this->setNumArmies(order.numArmies);
    }
    return *this;
}

int OrdersDeploy::getNumArmies() const{
    return this->numArmies;
}
void OrdersDeploy::setNumArmies(int numArmies) {
    this->numArmies = numArmies;
}

Orders* OrdersDeploy::allocateClone() const{
    return new OrdersDeploy(*this);
}
void OrdersDeploy::printOrder(std::ostream& strm) const{
    strm << "Player " << this->getIssuingPlayer()->getName() << " has deployed " <<  this->getNumArmies() << " units to " << *this->getSourceTerritory(); //changed the output text a little
}
bool OrdersDeploy::validate(){
    if (this->getSourceTerritory() == nullptr || this->getIssuingPlayer() == nullptr || this->getSourceTerritory()->getOwner() == nullptr)
        return false;
    // May have to add in equals functions
    if (this->getSourceTerritory()->getOwner()->equals(this->getIssuingPlayer())){
        cout << "VALID DEPLOY" << endl;
        return true;
    }
    cout << "Deploying to unowned territory is invalid" << endl;
    return false;
}
void OrdersDeploy::execute(){
    cout << "OrdersDeploy::execute" << endl;
}

OrdersAdvance::OrdersAdvance() : Orders(), targetTerritory(nullptr), numArmies(0) {}
OrdersAdvance::OrdersAdvance(Player* issuingPlayer, Territory* sourceTerritory, Territory* targetTerritory, int numArmies) : Orders(issuingPlayer, sourceTerritory), targetTerritory(targetTerritory), numArmies(numArmies){}
OrdersAdvance::OrdersAdvance(const OrdersAdvance& order) : Orders(order) {
    if (order.getTargetTerritory()){
        // this->targetTerritory = new Territory(*order.targetTerritory); // might be fine if Territory class has copy constructor and assignment operator
        this->targetTerritory = order.targetTerritory;
    }
    else   
        this->setTargetTerritory(nullptr);
    this->setNumArmies(order.getNumArmies());
}
OrdersAdvance::~OrdersAdvance(){}
OrdersAdvance& OrdersAdvance::operator=(const OrdersAdvance& order){
    if (this != &order){
        Orders::operator=(order);
        // delete this->getTargetTerritory();

        if (order.getTargetTerritory())
            // this->targetTerritory = new Territory(*order.targetTerritory); // might be fine if Territory class has copy constructor and assignment operator
            this->targetTerritory = order.targetTerritory;
        else
            this->setTargetTerritory(nullptr);
        this->setNumArmies(order.getNumArmies());
    }
    return *this;
}
Territory* OrdersAdvance::getTargetTerritory() const{
    return this->targetTerritory;
}
void OrdersAdvance::setTargetTerritory(Territory* targetTerritory){
    this->targetTerritory = targetTerritory;
}
int OrdersAdvance::getNumArmies() const{
    return this->numArmies;
}
void OrdersAdvance::setNumArmies(int numArmies) {
    this->numArmies = numArmies;
}
Orders* OrdersAdvance::allocateClone() const{
    return new OrdersAdvance(*this);
}
void OrdersAdvance::printOrder(std::ostream& strm) const{
    strm << "Player " << this->getIssuingPlayer()->getName() << " is advancing " << this->getNumArmies() << " armies from " << *this->getSourceTerritory() << " to " << *this->getTargetTerritory();
}
bool OrdersAdvance::validate(){
    if (this->getSourceTerritory() == nullptr || this->getIssuingPlayer() == nullptr || this->getTargetTerritory() == nullptr)
        return false;

    // May need to implement equals
    if (this->getSourceTerritory()->getOwner()->equals(this->getIssuingPlayer())){
        cout << "VALID ADVANCE" << endl;
        return true;
    }
    cout << "INVALID ADVANCE" << endl;
    return false;
}
void OrdersAdvance::execute(){
    cout << "OrdersAdvance::execute" << endl;
}

Orders* OrdersBomb::allocateClone() const{
    return new OrdersBomb(*this);
}
void OrdersBomb::printOrder(std::ostream& strm) const{
    strm << "Player " << this->getIssuingPlayer()->getName() << " has sent a bomb to " << *this->getSourceTerritory();
}
bool OrdersBomb::validate(){
    if (this->getSourceTerritory() == nullptr || this->getSourceTerritory()->getOwner() == nullptr || this->getIssuingPlayer() == nullptr)
        return false;

    if (this->getSourceTerritory()->getOwner()->equals(this->getIssuingPlayer())){
        cout << "Bombing own territory is invalid" << endl;
        return false;
    }
    cout << "VALID BOMBING" << endl;
    return true;
        
}
void OrdersBomb::execute(){
    cout << "OrdersBomb::execute" << endl;
}


Orders* OrdersBlockade::allocateClone() const{
    return new OrdersBlockade(*this);
}
void OrdersBlockade::printOrder(std::ostream& strm) const{
    strm << "Player " << this->getIssuingPlayer()->getName() << " is performing a blockade on " << *this->getSourceTerritory();
}
bool OrdersBlockade::validate(){
    if (this->getSourceTerritory() == nullptr || this->getIssuingPlayer() == nullptr)
        return false;

    if (this->getSourceTerritory()->getOwner()->equals(this->getIssuingPlayer())){
        cout << "VALID BLOCKADE" << endl;
        return true;
    }
    cout << "Blockade on territory that is not yours is invalid" << endl;
    return false;
}
void OrdersBlockade::execute(){
    cout << "OrdersBlockade::execute" << endl;
}

OrdersAirlift::OrdersAirlift() : Orders(), targetTerritory(nullptr), numArmies(0) {}
OrdersAirlift::OrdersAirlift(Player* issuingPlayer, Territory* sourceTerritory, Territory* targetTerritory, int numArmies) : Orders(issuingPlayer, sourceTerritory), targetTerritory(targetTerritory), numArmies(numArmies) {}
OrdersAirlift:: OrdersAirlift(const OrdersAirlift& order) : Orders(order) {
    if (order.getTargetTerritory())
        // this->targetTerritory = new Territory(*order.targetTerritory); // might be fine if Territory class has copy constructor and assignment operator
        this->targetTerritory = order.targetTerritory;
    else   
        this->setTargetTerritory(nullptr);
    this->setNumArmies(order.getNumArmies());

}
OrdersAirlift::~OrdersAirlift(){}
OrdersAirlift& OrdersAirlift::operator=(const OrdersAirlift& order){
    if (this != &order){
        Orders::operator=(order);
        // delete this->getTargetTerritory();

        if (order.getTargetTerritory())
            // this->targetTerritory = new Territory(*order.targetTerritory); // might be fine if Territory class has copy constructor and assignment operator
            this->targetTerritory = order.targetTerritory;
        else
            this->setTargetTerritory(nullptr);
        this->setNumArmies(order.getNumArmies());
    }
    return *this;
}
Territory* OrdersAirlift::getTargetTerritory() const{
    return this->targetTerritory;
}
void OrdersAirlift::setTargetTerritory(Territory* targetTerritory){
    this->targetTerritory = targetTerritory;
}
int OrdersAirlift::getNumArmies() const{
    return this->numArmies;
}
void OrdersAirlift::setNumArmies(int numArmies) {
    this->numArmies = numArmies;
}
Orders* OrdersAirlift::allocateClone() const{
    return new OrdersAirlift(*this);
}
void OrdersAirlift::printOrder(std::ostream& strm) const{
    strm << "Player " << this->getIssuingPlayer()->getName() << " is airlifting " << this->getNumArmies() << " from " << *this->getSourceTerritory() << "to " << *this->getTargetTerritory();
}
bool OrdersAirlift::validate(){
    if (this->getSourceTerritory() == nullptr || this->getIssuingPlayer() == nullptr || this->getTargetTerritory() == nullptr)
        return false;

    if (this->getSourceTerritory()->getOwner()->equals(this->getIssuingPlayer()) && this->getTargetTerritory()->getOwner()->equals(this->getIssuingPlayer())){
        cout << "VALID AIRLIFT" << endl;
        return true;
    }
    cout << "INVALID AIRLIFT" << endl;
    return false;
}
void OrdersAirlift::execute(){
    cout << "OrdersAirlift::execute" << endl;
}

OrdersNegotiate::OrdersNegotiate() : Orders(), enemyToTruce(nullptr) {}
OrdersNegotiate::OrdersNegotiate(Player* issuingPlayer, Player* enemyToTruce) : Orders(issuingPlayer, nullptr), enemyToTruce(enemyToTruce) {}
OrdersNegotiate::OrdersNegotiate(const OrdersNegotiate& order) : Orders(order){
    if (order.getEnemyToTruce())
        // this->enemyToTruce = new Player(*order.enemyToTruce); // might be fine if player class has copy constructor and assignment operator
        this->enemyToTruce = order.enemyToTruce;
}
OrdersNegotiate::~OrdersNegotiate(){}
OrdersNegotiate& OrdersNegotiate::operator=(const OrdersNegotiate& order){
    if (this != &order){
        Orders::operator=(order);
        // delete this->getEnemyToTruce();

        if (order.getEnemyToTruce())
            // this->enemyToTruce = new Player(*order.enemyToTruce); // might be fine if player class has copy constructor and assignment operator
            this->enemyToTruce = order.enemyToTruce;
        else
            this->setEnemyToTruce(nullptr);
    }
    return *this;
}
Player* OrdersNegotiate::getEnemyToTruce() const{
    return this->enemyToTruce;
}
void OrdersNegotiate::setEnemyToTruce(Player* enemyToTruce){
    this->enemyToTruce = enemyToTruce;
}
Orders* OrdersNegotiate::allocateClone() const{
    return new OrdersNegotiate(*this);
}
void OrdersNegotiate::printOrder(std::ostream& strm) const{
    strm << "Player " << this->getIssuingPlayer()->getName() << " is negotiating with Player " << this->getEnemyToTruce()->getName();
}
bool OrdersNegotiate::validate(){
    if (this->getEnemyToTruce() == nullptr || this->getIssuingPlayer() == nullptr)
        return false;

    if (this->getEnemyToTruce()->equals(this->getIssuingPlayer())){
        cout << "INVALID NEGOTIATION" << endl;
        return false;
    }
    cout << "VALID NEGOTIATE" << endl;
    return true;
        
}
void OrdersNegotiate::execute(){
    cout << "OrdersNegotiate::execute" << endl;
}


OrdersList::OrdersList() {}
OrdersList::OrdersList(OrdersList& orderList){
    for (auto iterator : orderList.list){
        this->list.push_back(iterator->allocateClone());
    }
}
OrdersList& OrdersList::operator=(const OrdersList& orderList){
    if (this != &orderList){
        for (auto order : this->list)
            delete order;

        this->list.clear();
        
        if (orderList.list.front()){
            for (auto order : orderList.list)
                this->list.push_back(order->allocateClone());
        }
    }  
    return *this;
}
OrdersList::~OrdersList(){
    for (auto order : this->list)
        delete order;
    
    this->list.clear();
}
std::list<Orders*> OrdersList::getList() const{
    return this->list;
}
std::list<Orders*>& OrdersList::getList(){ //non-const version for modification of the orderlist
    return this->list;
}
void OrdersList::setList(std::list<Orders*> list){
    for (auto order : this->list)
        delete order;

    this->list.clear();

    for (auto order : list)
        this->list.push_back(order->allocateClone());
}
Orders* OrdersList::add(Orders* order){
    if (order == nullptr)
        return nullptr;
    this->list.push_back(order);
    return order;
}
Orders* OrdersList::remove(const Orders& order){
    auto it = std::find(this->list.begin(), this->list.end(), &order);

    if (it != this->list.end()){
        this->list.erase(it);
        return *it;
    }
    cout << "Element not found" << endl;
    return nullptr;
}
Orders* OrdersList::remove(const int index){
    auto it = this->list.begin();
    std::advance(it, index);

    if (it != this->list.end()){
        this->list.erase(it);
        return *it;
    }
    cout << "Element not found" << endl;
    return nullptr;

}
Orders* OrdersList::move(const int sourceIndex, const int targetIndex){
    auto firstIterator = this->list.begin();
    std::advance(firstIterator, sourceIndex);

    Orders* movedOrder = *firstIterator;  // save pointer before moving

    auto secondIterator = this->list.begin();
    std::advance(secondIterator, targetIndex);

    this->list.splice(secondIterator, this->list, firstIterator);

    return movedOrder;

}