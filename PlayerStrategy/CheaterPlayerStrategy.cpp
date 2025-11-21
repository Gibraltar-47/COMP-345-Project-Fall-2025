//
// Created by Howard on 2025-11-16.
//

#include "CheaterPlayerStrategy.h"
#include <algorithm>
#include <unordered_set>
#include <iostream>

vector<Territory*> CheaterPlayerStrategy::toDefend(const std::vector<Territory*>& allTerritories) {                                                                            //Require changes to work as intended
    //Simply display what they control at the current moment
    std::vector<Territory*> defendList;
    struct Info { Territory* t; int threat; int armies; };

    std::vector<Info> infos;
    for (Territory* t : this->getPlayer()->getTerritories()) {
        if (!t) continue;
        int threatCount = 0;
        for (const std::string& adjName : t->getAdjTerritoriesNames()) {
            auto it = std::find_if(allTerritories.begin(), allTerritories.end(),
                                   [&](Territory* cand) { return cand && cand->getName() == adjName; });
            if (it != allTerritories.end()) {
                Territory* cand = *it;
                if (cand->getOwner() != this->getPlayer()) ++threatCount;
            }
        }
        infos.push_back({t, threatCount, t->getNumOfArmies()});
    }

    // Sort by descending threat (border territories first), then ascending armies (weaker first)
    std::sort(infos.begin(), infos.end(), [](const Info& a, const Info& b) {
        if (a.threat != b.threat) return a.threat > b.threat;
        return a.armies < b.armies;
    });

    for (auto &i : infos) defendList.push_back(i.t);
    return defendList;

}

vector<Territory *> CheaterPlayerStrategy::toAttack(const std::vector<Territory *> &allTerritories) {
    //Auto Capture




    std::vector<Territory*> attackList;
    // Build quick lookup of territories this player owns (by pointer and by name)
    std::unordered_set<Territory*> ownedPtrs;
    unordered_set<std::string> ownedNames;
    for (Territory* t : this->getPlayer()->getTerritories()) {
        if (t) {
            ownedPtrs.insert(t);
            ownedNames.insert(t->getName());
        }
    }

    for (Territory* myT : this->getPlayer()->getTerritories()) {
        if (!myT) continue;
        for (const std::string& adjName : myT->getAdjTerritoriesNames()) {
            auto it = std::find_if(allTerritories.begin(), allTerritories.end(),
                                   [&](Territory* cand) { return cand && cand->getName() == adjName; });
            if (it == allTerritories.end()) continue;

            Territory* target = *it;
            if (!target) continue;

            // Skip if target is one of this player's territories (by pointer or by matching name)
            if (ownedPtrs.count(target) || ownedNames.count(target->getName())) continue;

            // avoid duplicates
            if (std::find(attackList.begin(), attackList.end(), target) == attackList.end()) {
                attackList.push_back(target);
            }
        }
    }

    // sort by ascending defending armies (easier targets first)
    std::sort(attackList.begin(), attackList.end(),
              [](Territory* a, Territory* b) { return a->getNumOfArmies() < b->getNumOfArmies(); });

    return attackList;

}

void CheaterPlayerStrategy::issueOrder(Deck &deck, int mode, Territory *sourceTerritory, int numArmies, Territory *targetTerritory, Player &player2, Observer *obs) {
    //Does not actually issue orders
}




