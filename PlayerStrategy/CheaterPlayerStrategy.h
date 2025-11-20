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
    CheaterPlayerStrategy(Player* player);
    ~CheaterPlayerStrategy();
    void toAttack() override;
    void toDefend() override;
    void issueOrder() override;
};


#endif //COMP_345_PROJECT_FALL_2025_2_CHEATERPLAYER_H