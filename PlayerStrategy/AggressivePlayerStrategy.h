//
// Created by Admin on 2025-11-18.
//

#ifndef COMP_345_PROJECT_FALL_2025_AGGRESSIVEPLAYERSTRATEGY_H
#define COMP_345_PROJECT_FALL_2025_AGGRESSIVEPLAYERSTRATEGY_H
#include "PlayerStrategy.h"


class AggressivePlayerStrategy: public PlayerStrategy {
    public:
    AggressivePlayerStrategy();
    AggressivePlayerStrategy(Player* player): PlayerStrategy(player, StrategyType::Aggressive) {};
    ~AggressivePlayerStrategy() = default;

    vector<Territory *> toAttack(const std::vector<Territory *> &allTerritories) override;
    vector<Territory *> toDefend(const std::vector<Territory *> &allTerritories) override;
    void issueOrder(Deck &deck, int mode, Territory *sourceTerritory, int numArmies, Territory *targetTerritory, Player &player2, Observer *obs) override;
};


#endif //COMP_345_PROJECT_FALL_2025_AGGRESSIVEPLAYERSTRATEGY_H