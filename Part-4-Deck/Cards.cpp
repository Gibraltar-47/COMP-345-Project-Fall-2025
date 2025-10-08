

#include <algorithm>
#include <string>
#include <vector>
#include <iostream>
#include <random>

#include "Cards.h"
#include "../Orders/Orders.h"

using namespace std;

//Card Class=====================
//Default Constructor
Card::Card() {
    this->name = new string("BLANK");
}
//Parameterized Constructor
Card::Card(const string& name) {
    this->name = new string(name);
}
//Copy Constructor
Card::Card(const Card& other) {
    this->name = new string(*other.name);
}
//Assignment Operator
Card& Card::operator = (const Card& other) {
    if (this != &other) {
        delete this->name;
        name = new string(*other.name);
    }
    return *this;
}
//Destructor
Card::~Card() {
    delete name;
}
//Getter
string Card::getName() const {
    return *name;
}
//Setter
void Card::setName(const string& n) {
    *name = n;
}
void Card::play(Deck& deck, Hand* hand, OrdersList& olist, Player* player, Territory* territory) {


    olist.add(new OrdersBomb(player, territory)); //Only creates a bomb order for now


    hand->removeCard(this); //removes from hand
    deck.addCard(this); //add the card back to the deck

}
//Stream Insertion Operator
ostream& operator << (ostream& os, const Card& card) {
    os << *card.name;
    return os;
}


//Deck Class=====================
//Default Constructor
Deck::Deck(){
}
//Parameterized Constructor
Deck::Deck(const vector<Card*>& cards) {
    for (Card* card : cards) {
        this->cards.push_back(new Card(*card));
    }
}
//Copy Constructor
Deck::Deck(const Deck &other) {
    for (const Card* card : other.cards) {
        cards.push_back(new Card(*card));
    }
}
//Assignment Operator
Deck& Deck::operator=(const Deck& other) {
    if (this != &other) {
        for (Card* card : cards) {
            delete card;
        }
        cards.clear();
        for (Card* card : other.cards) {
            cards.push_back(new Card(*card));
        }
    }
    return *this;
}
//Destructor
Deck:: ~Deck() {
    cout<< "deleting cards" << endl;
    for (Card* card: cards) {
        delete card;
    }
    cout<< "deck deleted" << endl;
    cards.clear();
}
//Getter
int Deck::getDeckSize() const {                                                                                         //Deck size
    return cards.size();
}

//Methods
void Deck::addCard(Card* card) {                                                                                        //Adding cards to the deck
    cards.push_back(card);
}

Card* Deck::draw() {                                                                                                    //Removes a card from the deck and return it
    if (cards.empty()) {throw out_of_range("Deck is empty");}

    static random_device rd;
    static default_random_engine generator(rd()); //Shuffler
    uniform_int_distribution<int> distribution(0, cards.size() - 1);                                                //Range
    int i = distribution(generator);                                                                                 //Random result

    Card* card = cards[i];
    cards.erase(cards.begin() + i);
    return card;
}
//Boolean Methods
bool Deck::isEmpty() const {
    return cards.empty();
}
//Stream Insertion Operator
ostream& operator << (ostream& os, const Deck& deck) {
    os << "Deck contains " << deck.getDeckSize() << " cards." << endl;
    os << "Deck Content: ";
    for (size_t i = 0; i < deck.getDeckSize(); i++) {
        os << *deck.cards[i];
        if (i < deck.getDeckSize() - 1) {
            os << ", ";
        }
    }
    return os;
}

//Hand Class=====================
//Default Constructor
Hand::Hand() {
    this->player = new string("BLANK");
}
//Parameterized Constructor
Hand::Hand(const string& name) {
    this->player = new string(name);
}
//Copy Constructor
Hand::Hand(const Hand& other){
    this->player = new string(*other.player);
    for (Card* c : other.cards) {
        this->cards.push_back(new Card(*c));
    }
}

//Assignment Operator
Hand& Hand::operator=(const Hand& other) {
    if (this != &other) {
        delete player;
        player = new string(*other.player);

        cards = other.cards;
    }
    return *this;
}
//Destructor
Hand::~Hand() {                                                                                                         //Since the cards are owned by the Deck,
    //delete player;                                                                                                      //all cards inside a hand vector are borrowed objects
    cards.clear();                                                                                                      //cards wont be deleted from the hand. (see returnAll())
}
//Methods
void Hand::addCard(Card* card) {                                                                                        //Adding cards to the list
    cards.push_back(card);
    cout << *player << " has drawn " << card->getName() << endl;
}
void Hand::draw(Deck& deck) {                                                                                           //Draw (RNG)
    cards.push_back(deck.draw());
    cout << *player << " has drawn " << cards.back()->getName() << endl;
}
void Hand::returnAll(Deck& deck) {                                                                                      //Whenever a player loses, all their cards are returned to the deck.
    for (Card* card : cards) {
        deck.addCard(card);
    }
    cards.clear();
}

void Hand::removeCard(Card* card) {
    cards.erase(std::remove(cards.begin(), cards.end(), card), cards.end());
}

//Boolean Method
bool Hand::isEmpty() const {
    return cards.empty();
}
//Stream Insertion Operator
ostream& operator << (ostream& os, const Hand& hand) {
    os << *hand.player << "'s hand: ";
    if (hand.cards.empty()) {
        os << "(EMPTY)";
    }
    else {
        for (size_t i = 0; i < hand.cards.size(); i++) {
            os << *hand.cards[i];
            if (i < hand.cards.size() - 1) {
                os << ", ";
            }
        }
    }
    return os;
}
//=======================================================
//Temporary
void Hand::playCard(Deck& deck, const string& cardName, OrdersList& olist,Player* p, Territory* territory) {
    //Plays a card
    if (isEmpty()) {                                                                                                    //Checks if hand is empty
        cout << *player << "'s hand is empty" << endl;
        return;
    }

    auto it = find_if(cards.begin(), cards.end(),                                   //Locates the played card
    [&] (Card* c) { return c->getName() == cardName; });

    if (it == cards.end()) {                                                                                            //If played card is not found in hand
        cout << *player << " does not have " << cardName << endl;
        return;
    }

    Card* used = *it;
    cout << *player << " has played " << used->getName() << "!" << endl;
    used->play(deck, this,olist,p, territory);

    //Returns the card back to the deck
    cout << used->getName() << " goes back into the deck." << endl;
}

//TEMPORARY
// Order::Order(std::string &name) {
//     this->name = new string(name);
// }

// Order::~Order() {
//     cout << *this->name << " deleted" << endl;
//     delete name;
// }

// OrderList::OrderList() = default;

// OrderList::~OrderList() {
//     cout << "Resolving Orders: " << endl;
//     for (Order* o: olist) {
//         delete o;
//     }
//     olist.clear();
//     cout << endl;
//     cout << "List has been deleted" << endl;
// }
// void OrderList::addOrder(Order *order) {
//     this->olist.push_back(order);
// }
// void OrderList::resolveOrder() {
//     delete this;
// }



