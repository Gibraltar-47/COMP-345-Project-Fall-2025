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
    NeutralPlayerStrategy(Player* player);
    ~NeutralPlayerStrategy();

    void toAttack() override;
    void toDefend() override;
    void issueOrder() override;

};


#endif //COMP_345_PROJECT_FALL_2025_2_NEUTRALPLAYER_H