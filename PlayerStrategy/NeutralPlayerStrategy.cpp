//
// Created by Howard on 2025-11-16.
//

#include "NeutralPlayerStrategy.h"

#include "AggressivePlayerStrategy.h"
#include <algorithm>

vector<Territory *> NeutralPlayerStrategy::toAttack(const std::vector<Territory *> &allTerritories) {
    //Do nothing since it wont attack anything
    return {};
}
vector<Territory *> NeutralPlayerStrategy::toDefend(const std::vector<Territory *> &allTerritories) {

    return this->getPlayer()->getTerritories();
}
void NeutralPlayerStrategy::issueOrder(Deck &deck, int mode, Territory *sourceTerritory, int numArmies, Territory *targetTerritory, Player &player2, Observer *obs) {
    //Skipping since not issuing orders
}

void NeutralPlayerStrategy::attacked() {
    this->getPlayer()->setPlayerStrategy(new AggressivePlayerStrategy(this->getPlayer()));
}





