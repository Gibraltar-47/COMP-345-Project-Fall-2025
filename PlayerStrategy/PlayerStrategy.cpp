//
// Created by Howard on 2025-11-16.
//

#include "PlayerStrategy.h"

#include <algorithm>
#include <unordered_set>

#include "Orders.h"


PlayerStrategy::PlayerStrategy(Player* player)
{
    this->player = player;
}

AggressivePlayerStrategy::AggressivePlayerStrategy(Player* player): PlayerStrategy(player){}

void AggressivePlayerStrategy::issueOrder(Deck& deck, int mode, Territory* sourceTerritory, int numArmies, Territory* targetTerritory, Player& player2,Observer* obs)
{

    switch (mode) {
    case 1: //Deploy
        {
            player->addOrder(new OrdersDeploy(player,sourceTerritory,numArmies,obs));
            int temp =player->getNumFreeArmies() ;
            temp-= numArmies;
            player->setNumFreeArmies(temp);
            break;
        }
    case 2: //Advance
        {
            player->addOrder(new OrdersAdvance(player,sourceTerritory,targetTerritory, numArmies,obs));
            int temp1 =player->getNumFreeArmies() ;
            temp1-= numArmies;
            player->setNumFreeArmies(temp1);
            break;
        }
    case 3:
    case 4:
    case 5:
    case 6: {
            Card* matchingCard = nullptr;
            for (Card* card: player->getHand()->getCards()) {
                if ((mode == 3 && card->getName() == "Bomb") ||
                    (mode == 4 && card->getName() == "Blockade") ||
                    (mode == 5 && card->getName() == "Airlift") ||
                    (mode == 6 && card->getName() == "Diplomacy")) {
                    matchingCard = card;
                    break;
                    }
            }
            if (!matchingCard) {
                cout << player->getName() << " doesn't have the card required for this order." << endl;
                return;
            }
            OrdersList* olist = player->getOrderList();

            matchingCard->play(deck, player->getHand(), *olist, player, sourceTerritory,mode,numArmies,targetTerritory,&player2, obs);

            int temp2 =player->getNumFreeArmies() ;
            temp2-= numArmies;
            player->setNumFreeArmies(temp2);
            cout << player->getHand() << " played a " << matchingCard->getName() << " card." << endl;
            break;

    }
    default:
        cout << "Invalid order mode." << endl;

    }
}

vector<Territory*> AggressivePlayerStrategy::toAttack(const std::vector<Territory*>& allTerritories)
{

    vector<Territory*> territories = PlayerStrategy::player->getTerritories();
    std::vector<Territory*> defendList;
    std::vector<Territory*> attackList;

    // Build quick lookup of territories this player owns (by pointer and by name)
    unordered_set<Territory*> ownedPtrs;
    unordered_set<std::string> ownedNames;
    for (Territory* t : territories) {
        if (t) {
            ownedPtrs.insert(t);
            ownedNames.insert(t->getName());
        }
    }

    for (Territory* myT : territories) {
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

    vector<Territory*> list;

    // sort by ascending defending armies (easier targets first)
    std::sort(attackList.begin(), attackList.end(),
    [](Territory* a, Territory* b) { return a->getNumOfArmies() < b->getNumOfArmies(); });


    for (Territory* t: attackList)
    {
        for (const string& n: PlayerStrategy::player->toDefend(territories).front()->getAdjTerritoriesNames())
        {
            if (t->getName()==n)
            {
                list.push_back(t);
            }
        }
    }
    return list;
}

vector<Territory*> AggressivePlayerStrategy::toDefend(const std::vector<Territory*>& allTerritories)
{
    vector<Territory*> territories = PlayerStrategy::player->getTerritories();
    std::vector<Territory*> defendList;
    struct Info { Territory* t; int threat; int armies; };

    std::vector<Info> infos;
    for (Territory* t : territories) {
        if (!t) continue;
        int threatCount = 0;
        for (const std::string& adjName : t->getAdjTerritoriesNames()) {
            auto it = std::find_if(allTerritories.begin(), allTerritories.end(),
                                   [&](Territory* cand) { return cand && cand->getName() == adjName; });
            if (it != allTerritories.end()) {
                Territory* cand = *it;
                if (cand->getOwner() != PlayerStrategy::player) ++threatCount;
            }
        }
        infos.push_back({t, threatCount, t->getNumOfArmies()});
    }

    // Sort by descending threat (border territories first), then ascending armies (weaker first)
    std::sort(infos.begin(), infos.end(), [](const Info& a, const Info& b) {
        if (a.threat != b.threat) return a.threat > b.threat;
        return a.armies < b.armies;
    });

    defendList.push_back(infos.back().t);
    return defendList;
}

