#include "PlayerStrategy.h"
#include "Player.h"

using namespace std;
PlayerStrategy::PlayerStrategy(Player* p): player(p) {}
void PlayerStrategy::setPlayer(Player* p) {
    player = p;
}
Player* PlayerStrategy::getPlayer() {
    return player;
}
HumanPlayerStrategy::HumanPlayerStrategy(Player* p): PlayerStrategy(p) {}

vector<Territory*> HumanPlayerStrategy::toDefend(vector<Territory*> territories, vector<Territory*> allTerritories, Player* p) {
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
                if (cand->getOwner()->getName() != p->getName()) ++threatCount;
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

vector<Territory*> HumanPlayerStrategy::toAttack(vector<Territory*> territories, vector<Territory*> allTerritories, Player* p) {
    return player->getAdjacentEnemyTerritories();
}

void HumanPlayerStrategy::issueOrder(Deck& deck, int mode, Territory* sourceTerritory, int numArmies, Territory* targetTerritory, Player& player2,Observer* obs,Player* p) {
    switch (mode) {
        case 1: //Deploy
            p->getOrderList->add(new OrdersDeploy(this,sourceTerritory,numArmies,obs));
            break;
        case 2: //Advance
             p->getOrderList->add(new OrdersAdvance(this,sourceTerritory,targetTerritory, numArmies,obs));
            break;
        case 3:
        case 4:
        case 5:
        case 6: {
            Hand 
            Card* matchingCard = nullptr;
            for (Card* card: p->getHand->getCards()) {
                if ((mode == 3 && card->getName() == "Bomb") ||
                    (mode == 4 && card->getName() == "Blockade") ||
                    (mode == 5 && card->getName() == "Airlift") ||
                    (mode == 6 && card->getName() == "Diplomacy")) {
                    matchingCard = card;
                    break;
                    }
            }
            if (!matchingCard) {
                cout << name << " doesn't have the card required for this order." << endl;
                return;
            }
            OrdersList* olist = this->getOrderList();

            matchingCard->play(deck, hand, *olist, this, sourceTerritory,mode,numArmies,targetTerritory,&player2, obs); //dereference problem
            cout << name << " played a " << matchingCard->getName() << " card." << endl;
            break;

        }
        default:
            cout << "Invalid order mode." << endl;

    
}
  }
