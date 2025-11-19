#ifndef PLAYERSTRATEGY_H
#define PLAYERSTRATEGY_H

#include <vector>
#include <string>
class Player;
class Territory;

class PlayerStrategy {
protected:
    Player* player;   

public:
    PlayerStrategy(Player* p);
    virtual ~PlayerStrategy() = default;
    virtual std::vector<Territory*> toAttack(vector<Territory*> territories, vector<Territory*> allTerritories,Player* p) = 0;
    virtual std::vector<Territory*> toDefend(vector<Territory*> territories, vector<Territory*> allTerritories,Player* p) = 0;
    virtual void issueOrder(Deck& deck, int mode, Territory* sourceTerritory, int numArmies, Territory* targetTerritory, Player& player2,Observer* obs) = 0;
    Player* getPlayer() const { return player; }
};
class HumanPlayerStrategy : public PlayerStrategy {
public:
    HumanPlayerStrategy(Player* p);
    ~HumanPlayerStrategy() override = default;

    std::vector<Territory*> toAttack(vector<Territory*> territories, vector<Territory*> allTerritories,Player* p) override;
    std::vector<Territory*> toDefend(vector<Territory*> territories, vector<Territory*> allTerritories,Player* p) override;
    void issueOrder(Deck& deck, int mode, Territory* sourceTerritory, int numArmies, Territory* targetTerritory, Player& player2,Observer* obs) override;     //asks user for user  input
};


#endif