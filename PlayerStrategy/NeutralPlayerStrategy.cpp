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
void NeutralPlayerStrategy::issueOrder(Deck &deck, int mode, Territory *sourceTerritory, int numArmies, Territory *targetTerritory, Player &player2, Observer *obs) {
    //Skipping since not issuing orders
}

void NeutralPlayerStrategy::attacked() {
    this->getPlayer()->setPlayerStrategy(new AggressivePlayerStrategy(this->getPlayer()));
}





