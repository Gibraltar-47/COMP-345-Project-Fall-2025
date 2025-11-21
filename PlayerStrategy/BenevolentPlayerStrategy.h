//
// Created by Admin on 2025-11-20.
//

#ifndef COMP_345_PROJECT_FALL_2025_BENEVOLENTPLAYERSTRATEGY_H
#define COMP_345_PROJECT_FALL_2025_BENEVOLENTPLAYERSTRATEGY_H
#include "PlayerStrategy.h"


class BenevolentPlayerStrategy: public PlayerStrategy {
public:
    BenevolentPlayerStrategy();
    BenevolentPlayerStrategy(Player* player): PlayerStrategy(player, StrategyType::Benevolent) {};
    ~BenevolentPlayerStrategy() = default;

    vector<Territory *> toAttack(const std::vector<Territory *> &allTerritories) override;
    vector<Territory *> toDefend(const std::vector<Territory *> &allTerritories) override;
    void issueOrder(Deck &deck, int mode, Territory *sourceTerritory, int numArmies, Territory *targetTerritory, Player &player2, Observer *obs) override;
};


#endif //COMP_345_PROJECT_FALL_2025_BENEVOLENTPLAYERSTRATEGY_H