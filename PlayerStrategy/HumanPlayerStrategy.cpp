//
// Created by Admin on 2025-11-20.
//


#include "HumanPlayerStrategy.h"

void HumanPlayerStrategy::issueOrder(Deck &deck, int mode, Territory *sourceTerritory, int numArmies, Territory *targetTerritory, Player &player2, Observer *obs) {
    cout<< "Nothing to see here" << endl;
}


vector<Territory*> HumanPlayerStrategy::toDefend(const std::vector<Territory *> &allTerritories) {
    return {};
}

vector<Territory*> HumanPlayerStrategy::toAttack(const std::vector<Territory *> &allTerritories) {
    return {};
}