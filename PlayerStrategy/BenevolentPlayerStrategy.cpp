//
// Created by Admin on 2025-11-20.
//

#include "BenevolentPlayerStrategy.h"

void BenevolentPlayerStrategy::issueOrder(Deck &deck, int mode, Territory *sourceTerritory, int numArmies, Territory *targetTerritory, Player &player2, Observer *obs) {
    cout<< "Nothing to see here" << endl;
}


vector<Territory*> BenevolentPlayerStrategy::toDefend(const std::vector<Territory *> &allTerritories) {
    return {};
}

vector<Territory*> BenevolentPlayerStrategy::toAttack(const std::vector<Territory *> &allTerritories) {
    return {};
}