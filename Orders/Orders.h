#ifndef ORDERS_H
#define ORDERS_H

#include <iostream>
#include <list>
#include <algorithm>
#include <string>
using namespace std;

class Player;

class Territory{ 
    public:
        std::string name; int points;
        Player* owner;
        Territory();
        Territory(std::string name, int points, Player* owner);
        bool equals(Territory* territory2);
        friend std::ostream& operator<<(std::ostream &strm, const Territory& territory);
}; // Temporary (is replacing nodes from map)

class Player{
    public:
        int id;
        std::vector<Territory*> ownedTerritories;
        //OrdersList olist;
        Player();
        Player(int id);
        bool equals(Player* player2);
        friend std::ostream& operator<<(std::ostream &strm, const Player& player);
}; // Temporary (is replacing player class)

class Orders
{
private:
    Player* issuingPlayer;
    Territory* sourceTerritory;
    bool isActive;
    bool isValid;  
    
public:
    Orders();
    Orders(Player* issuingPlayer, Territory* sourceTerritory);
    Orders(const Orders& order);
    virtual ~Orders();
    Orders& operator=(const Orders& order);
    friend std::ostream& operator<<(std::ostream &strm, const Orders& order);
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
    virtual bool validate();
    virtual void execute();
};

class OrdersDeploy: public Orders
{
    private:
        int numArmies;
    public:
        OrdersDeploy();
        OrdersDeploy(Player* issuingPlayer, Territory* sourceTerritory, int numArmies);
        OrdersDeploy(const OrdersDeploy& order);
        //~OrdersDeploy();
        OrdersDeploy& operator=(const OrdersDeploy& order);
        int getNumArmies() const;
        void setNumArmies(int numArmies);

        Orders* allocateClone() const override;
        void printOrder(std::ostream& strm) const override;
        bool validate() override;
        void execute() override;
};

class OrdersAdvance: public Orders
{
    private:
        Territory* targetTerritory;
        int numArmies;

    public:
        OrdersAdvance();
        OrdersAdvance(Player* issuingPlayer, Territory* sourceTerritory, Territory* targetTerritory, int numArmies);
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
};

class OrdersBomb: public Orders
{
    public:
        // Might be able to inherit constrcutors and assignment overload with this
        // since this class does not introduce any new data members
        using Orders::Orders;
        using Orders::operator=;

        // OrdersBomb();
        // OrdersBomb(Territory* sourceTerritory);
        // OrdersBomb(const OrdersBomb& order);
        // ~OrdersBomb();
        // OrdersBomb& operator=(const OrdersBomb& order);

        Orders* allocateClone() const override;
        void printOrder(std::ostream& strm) const override;
        bool validate() override;
        void execute() override;
};

class OrdersBlockade: public Orders
{
    public:
        // Might be able to inherit constrcutors and assignment overload with this
        // since this class does not introduce any new data members
        using Orders::Orders;
        using Orders::operator=;

        // OrdersBlockade();
        // OrdersBlockade(Territory* sourceTerritory);
        // OrdersBlockade(const OrdersBlockade& order);
        // ~OrdersBlockade();
        // OrdersBlockade& operator=(const OrdersBlockade& order);

        Orders* allocateClone() const override;
        void printOrder(std::ostream& strm) const override;
        bool validate() override;
        void execute() override;
};

class OrdersAirlift: public Orders
{
    private:
        Territory* targetTerritory;
        int numArmies;
    public:
        OrdersAirlift();
        OrdersAirlift(Player* issuingPlayer, Territory* sourceTerritory, Territory* targetTerritory, int numArmies);
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
};

class OrdersNegotiate: public Orders
{
    private:
        Player* enemyToTruce;
    public:
        OrdersNegotiate();
        OrdersNegotiate(Player* issuingPlayer, Player* enemyToTruce);
        OrdersNegotiate(const OrdersNegotiate& order);
        ~OrdersNegotiate();
        OrdersNegotiate& operator=(const OrdersNegotiate& order);
        Player* getEnemyToTruce() const;
        void setEnemyToTruce(Player* enemyToTruce);

        Orders* allocateClone() const override;
        void printOrder(std::ostream& strm) const override;
        bool validate() override;
        void execute() override;
};

class OrdersList
{
    private:
        std::list<Orders*> list;

    public:
        OrdersList();
        OrdersList(OrdersList& orderList);
        OrdersList& operator=(const OrdersList& orderList);
        ~OrdersList();
        std::list<Orders*> getList() const;
        void setList(std::list<Orders*> list);
        Orders* add(Orders* order);
        Orders* remove(const Orders& order);
        Orders* remove(const int index);
        Orders* move(const Orders& order, int position);
        Orders* move(const int sourceIndex, const int targetIndex);
};

#endif