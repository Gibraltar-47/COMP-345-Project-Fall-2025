//
// Created by Howard on 2025-09-21.
//

#include <algorithm>
#include <string>
#include <vector>
#include <iostream>
#include <random>

#include "Cards.h"

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
//Method
void Card::order() const { //Currently a placeholder function
    cout << *name << " is placed into order. " << endl;                                                                 //Replace with actual order later on. Currently just a placeholder
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
    for (Card* card: cards) {
        delete card;
    }
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

    static random_device random;                                                                                        //Random seed
    static default_random_engine generator(random());                                                                 //Shuffler
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
    os << "Deck contains: ";
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
    this->cards = other.cards;
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
    delete player;                                                                                                      //all cards inside a hand vector are borrowed objects
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
void Hand::play(Deck& deck, const string& cardName) {                                                                   //Plays a card
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
    used->order();                                                                                                      //Sends the card to order list (placeholder for now)

    cards.erase(it);                                                                                                 //Removes from hand
    deck.addCard(used);                                                                                                 //Returns the card back to the deck
    cout << used->getName() << " goes back into the deck." << endl;
}
void Hand::returnAll(Deck& deck) {                                                                                      //Whenever a player loses, all their cards are returned to the deck.
    for (Card* card : cards) {
        deck.addCard(card);
    }
    cards.clear();
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

