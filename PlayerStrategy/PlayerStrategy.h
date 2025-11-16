//
// Created by Howard on 2025-11-16.
//

#ifndef COMP_345_PROJECT_FALL_2025_2_PLAYERSTRATEGY_H
#define COMP_345_PROJECT_FALL_2025_2_PLAYERSTRATEGY_H

#include "Player.h"


class PlayerStrategy {
private:
    Player* player;

public:
    PlayerStrategy();
    PlayerStrategy(Player* player): player(player) {};

    virtual ~PlayerStrategy() = default;

    virtual void issueOrder() = 0;
    virtual void toAttack() = 0;
    virtual void toDefend() = 0;


};


#endif //COMP_345_PROJECT_FALL_2025_2_PLAYERSTRATEGY_H