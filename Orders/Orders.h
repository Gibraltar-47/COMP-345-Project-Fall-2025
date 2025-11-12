#ifndef ORDERS_H
#define ORDERS_H

#include <iostream>
#include <list>
#include <algorithm>
#include <string>
#include <stdlib.h>
#include <time.h>
#include "LoggingObserver.h"
using namespace std;

class Player;
class OrdersList;
class Territory;

class Orders : public Subject, public ILoggable
{
private:
    Player* issuingPlayer;
    Territory* sourceTerritory;
    bool isActive;
    bool isValid;

public:
    Orders();
    Orders(Player* issuingPlayer, Territory* sourceTerritory,Observer* obs);
    Orders(const Orders& order);
    virtual ~Orders();
    Orders& operator=(const Orders& order);
    friend std::ostream& operator<<(std::ostream& strm, const Orders& order);
    Player* getIssuingPlayer() const;
    void setIssuingPlayer(Player* issuingPlayer);
    Territory* getSourceTerritory() const;
    void setSourceTerritory(Territory* sourceTerritory);
    bool getIsActive() const;
    void setIsActive(bool isActive);
    bool getIsValid() const;
    void setIsValid(bool isValid);

    virtual Orders* allocateClone() const;
    virtual void printOrder(std::ostream& strm) const;
    virtual bool validate() = 0;
    virtual void execute() = 0;

    void notify(ILoggable& subject) override;
    virtual string stringToLog()=0;
    virtual string stringTo()=0;
};

class OrdersDeploy : public Orders
{
private:
    int numArmies;

public:
    OrdersDeploy();
    OrdersDeploy(Player* issuingPlayer, Territory* sourceTerritory, int numArmies,Observer* obs);
    OrdersDeploy(const OrdersDeploy& order);
    //~OrdersDeploy();
    OrdersDeploy& operator=(const OrdersDeploy& order);
    int getNumArmies() const;
    void setNumArmies(int numArmies);

    Orders* allocateClone() const override;
    void printOrder(std::ostream& strm) const override;
    bool validate() override;
    void execute() override;

    string stringToLog() override;
    string stringTo();
};

class OrdersAdvance : public Orders
{
private:
    Territory* targetTerritory;
    int numArmies;

public:
    OrdersAdvance();
    OrdersAdvance(Player* issuingPlayer, Territory* sourceTerritory, Territory* targetTerritory, int numArmies,Observer* obs);
    OrdersAdvance(const OrdersAdvance& order);
    ~OrdersAdvance();
    OrdersAdvance& operator=(const OrdersAdvance& order);
    Territory* getTargetTerritory() const;
    void setTargetTerritory(Territory* targetTerritory);
    int getNumArmies() const;
    void setNumArmies(int numArmies);

    Orders* allocateClone() const override;
    void printOrder(std::ostream& strm) const override;
    bool validate() override;
    void execute() override;

    string stringToLog() override;
    string stringTo();
};

class OrdersBomb : public Orders
{
public:
    using Orders::Orders;
    using Orders::operator=;

    Orders* allocateClone() const override;
    void printOrder(std::ostream& strm) const override;
    bool validate() override;
    void execute() override;

    string stringToLog() override;
    string stringTo();
};

class OrdersBlockade : public Orders
{
public:
    using Orders::Orders;
    using Orders::operator=;

    static Player* neutralPlayer;
    Orders* allocateClone() const override;
    void printOrder(std::ostream& strm) const override;
    bool validate() override;
    void execute() override;

    string stringToLog() override;
    string stringTo();
};

class OrdersAirlift : public Orders
{
private:
    Territory* targetTerritory;
    int numArmies;

public:
    OrdersAirlift();
    OrdersAirlift(Player* issuingPlayer, Territory* sourceTerritory, Territory* targetTerritory, int numArmies,Observer* obs);
    OrdersAirlift(const OrdersAirlift& order);
    ~OrdersAirlift();
    OrdersAirlift& operator=(const OrdersAirlift& order);
    Territory* getTargetTerritory() const;
    void setTargetTerritory(Territory* targetTerritory);
    int getNumArmies() const;
    void setNumArmies(int numArmies);

    Orders* allocateClone() const override;
    void printOrder(std::ostream& strm) const override;
    bool validate() override;
    void execute() override;

    string stringToLog() override;
    string stringTo();
};

class OrdersNegotiate : public Orders
{
private:
    Player* enemyToTruce;

public:
    OrdersNegotiate();
    OrdersNegotiate(Player* issuingPlayer, Player* enemyToTruce,Observer* obs);
    OrdersNegotiate(const OrdersNegotiate& order);
    ~OrdersNegotiate();
    OrdersNegotiate& operator=(const OrdersNegotiate& order);
    Player* getEnemyToTruce() const;
    void setEnemyToTruce(Player* enemyToTruce);

    Orders* allocateClone() const override;
    void printOrder(std::ostream& strm) const override;
    bool validate() override;
    void execute() override;

    string stringToLog() override;
    string stringTo();
};

class OrdersList : public Subject, public ILoggable
{
private:
    std::list<Orders*> list;

public:
    OrdersList(Observer* obs);
    OrdersList(OrdersList& orderList,Observer* obs);
    OrdersList& operator=(const OrdersList& orderList);
    ~OrdersList();
    friend std::ostream& operator<<(std::ostream& strm, const OrdersList& orderList);
    std::list<Orders*> getList() const;
    std::list<Orders*>& getList();
    void setList(std::list<Orders*> list);
    Orders* add(Orders* order);
    Orders* remove(const Orders& order);
    Orders* remove(const int index);
    // Orders* move(const Orders& order, int position);
    Orders* move(const int sourceIndex, const int targetIndex);

    void notify(ILoggable& subject) override;
    string stringToLog() override;
};

#endif
