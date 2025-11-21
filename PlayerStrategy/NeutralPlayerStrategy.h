//
// Created by Howard on 2025-11-16.
//

#ifndef COMP_345_PROJECT_FALL_2025_2_NEUTRALPLAYER_H
#define COMP_345_PROJECT_FALL_2025_2_NEUTRALPLAYER_H
#include "PlayerStrategy.h"



class NeutralPlayerStrategy: public PlayerStrategy {
    private:
        bool isAttacked;

    public:
    NeutralPlayerStrategy();
    NeutralPlayerStrategy(Player* player): PlayerStrategy(player, StrategyType::Neutral) {};

    ~NeutralPlayerStrategy() = default;

    std::vector<Territory*> toAttack(const std::vector<Territory*>& allTerritories) override;
    std::vector<Territory*> toDefend(const std::vector<Territory*>& allTerritories) override;
    void issueOrder(Deck& deck, int mode, Territory* sourceTerritory, int numArmies, Territory* targetTerritory, Player& player2,Observer* obs) override;

    void attacked();

};


#endif //COMP_345_PROJECT_FALL_2025_2_NEUTRALPLAYER_H