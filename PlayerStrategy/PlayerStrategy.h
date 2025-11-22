//
// Created by Howard on 2025-11-16.
//

#ifndef COMP_345_PROJECT_FALL_2025_2_PLAYERSTRATEGY_H
#define COMP_345_PROJECT_FALL_2025_2_PLAYERSTRATEGY_H

#include "../Player/Player.h"
#include <vector>
class Player;
class Territory;


enum class StrategyType {
    Human,
    Aggressive,
    Benevolent,
    Neutral,
    Cheater
};
class PlayerStrategy {
protected:
    StrategyType type;
    Player* getPlayer() const;

private:
    Player* player;

public:
    PlayerStrategy();
    PlayerStrategy(Player* player, StrategyType t): player(player), type(t) {};


    StrategyType getType() const;
    void setType(StrategyType t);

    virtual ~PlayerStrategy() = default;

    virtual void issueOrder(Deck& deck, int mode, Territory* sourceTerritory, int numArmies, Territory* targetTerritory, Player& player2,Observer* obs) = 0;
    virtual std::vector<Territory*> toAttack(const std::vector<Territory*>& allTerritories) = 0;
    virtual std::vector<Territory*> toDefend(const std::vector<Territory*>& allTerritories) = 0;

    void attacked();
};


#endif //COMP_345_PROJECT_FALL_2025_2_PLAYERSTRATEGY_H