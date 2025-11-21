//
// Created by Admin on 2025-11-18.
//

#include "AggressivePlayerStrategy.h"


//empty for now
void AggressivePlayerStrategy::issueOrder(Deck &deck, int mode, Territory *sourceTerritory, int numArmies, Territory *targetTerritory, Player &player2, Observer *obs) {
    cout<< "Nothing to see here" << endl;
}


vector<Territory*> AggressivePlayerStrategy::toDefend(const std::vector<Territory *> &allTerritories) {
    return {};
}

vector<Territory*> AggressivePlayerStrategy::toAttack(const std::vector<Territory *> &allTerritories) {
    return {};
}
