//
// Created by Howard on 2025-11-16.
//


#include "PlayerStrategy.h"

Player *PlayerStrategy::getPlayer() const {
    return this->player;
}


PlayerStrategy::PlayerStrategy() {
    this->player = nullptr;
}


StrategyType PlayerStrategy::getType() const {
    return type;
}

void PlayerStrategy::setType(StrategyType t) {
    type = t;
}



