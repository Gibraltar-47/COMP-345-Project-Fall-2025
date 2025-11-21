//
// Created by Howard on 2025-11-16.
//

#ifndef COMP_345_PROJECT_FALL_2025_2_CHEATERPLAYER_H
#define COMP_345_PROJECT_FALL_2025_2_CHEATERPLAYER_H
#include "PlayerStrategy.h"


class CheaterPlayerStrategy: public PlayerStrategy {
private:
public:
    CheaterPlayerStrategy();
    CheaterPlayerStrategy(Player* player): PlayerStrategy(player, StrategyType::Cheater) {};
    ~CheaterPlayerStrategy() = default ;


    vector<Territory*> toAttack(const std::vector<Territory*>& allTerritories) override;
    vector<Territory*> toDefend(const std::vector<Territory*>& allTerritories) override;
    void issueOrder(Deck& deck, int mode, Territory* sourceTerritory, int numArmies, Territory* targetTerritory, Player& player2,Observer* obs) override;
};


#endif //COMP_345_PROJECT_FALL_2025_2_CHEATERPLAYER_H