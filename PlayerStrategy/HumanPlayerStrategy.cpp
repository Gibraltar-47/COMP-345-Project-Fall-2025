//
// Created by Admin on 2025-11-20.
//


#include "HumanPlayerStrategy.h"
#include "../Orders/Orders.h"
#include <unordered_set>
#include <algorithm>

void HumanPlayerStrategy::issueOrder(Deck &deck, int mode, Territory *sourceTerritory, int numArmies, Territory *targetTerritory, Player &player2, Observer *obs) {

    switch (mode) {
        case 1: //Deploy
            this->getPlayer()->getOrderList()->add(new OrdersDeploy(this->getPlayer(),sourceTerritory,numArmies,obs));
            this->getPlayer()->removeNumFreeArmies(numArmies);
            break;
        case 2: //Advance
            this->getPlayer()->getOrderList()->add(new OrdersAdvance(this->getPlayer(),sourceTerritory,targetTerritory, numArmies,obs));
            this->getPlayer()->removeNumFreeArmies(numArmies);
            break;
        case 3:
        case 4:
        case 5:
        case 6: {
            Card* matchingCard = nullptr;
            for (Card* card: this->getPlayer()->getHand()->getCards()) {
                if ((mode == 3 && card->getName() == "Bomb") ||
                    (mode == 4 && card->getName() == "Blockade") ||
                    (mode == 5 && card->getName() == "Airlift") ||
                    (mode == 6 && card->getName() == "Diplomacy")) {
                    matchingCard = card;
                    break;
                    }
            }
            if (!matchingCard) {
                cout << this->getPlayer()->getName() << " doesn't have the card required for this order." << endl;
                return;
            }
            OrdersList* olist = this->getPlayer()->getOrderList();

            matchingCard->play(deck, this->getPlayer()->getHand(), *olist, this->getPlayer(), sourceTerritory,mode,numArmies,targetTerritory,&player2, obs); //dereference problem
            cout << this->getPlayer()->getName() << " played a " << matchingCard->getName() << " card." << endl;
            this->getPlayer()->removeNumFreeArmies(numArmies);
            break;

        }
        default:
            cout << "Invalid order mode." << endl;

    }
}


vector<Territory*> HumanPlayerStrategy::toDefend(const std::vector<Territory *> &allTerritories) {
    return this->getPlayer()->getTerritories();
}

vector<Territory*> HumanPlayerStrategy::toAttack(const std::vector<Territory *> &allTerritories) {
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