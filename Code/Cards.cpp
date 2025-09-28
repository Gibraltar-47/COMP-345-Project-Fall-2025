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
Card::Card(string name) : name(name) {}                                                                              //Constructor

string Card::getName() const {return name;}                                                                          //Getter


void Card::order(){
    cout << name << " is placed into order. " << endl;                                                                  //Replace with actual order later on. Currently just a placeholder
}


//Deck Class=====================
Deck::Deck(vector<Card> cards):  cards(cards) {}                                                                     //Constructor

void Deck::addCard(Card card) {                                                                                         //Adding cards to the deck
    cards.push_back(card);
}

void Deck::showDeck() const {                                                                                           //Reveals deck content
    cout << "Deck contains: ";
    if (cards.empty()) {
        cout << "(empty)";
    } else {
        for (const auto& c : cards) {
            cout << c.getName() << " ";
        }
    }
    cout << endl;
}

int Deck::getDeckSize() const {                                                                                         //Deck size
    return cards.size();
}

Card Deck::draw() {                                                                                                     //Removes a card from the deck and return it
    if (cards.empty()) {
        throw out_of_range("Deck is empty");
    }
    int index = rand() % cards.size();                                                                                  //RNG
    Card draw = cards[index];
    cards.erase(cards.begin() + index);
    return draw;
}

bool Deck::isEmpty() const {
    return cards.empty();
}


//Hand Class=====================
Hand::Hand(string name): player(name) {}                                                                             //Constructor

void Hand::addCard(const Card& card) {                                                                                  //Adding cards to the list
    cards.push_back(card);
    cout << player << " has drawn " << card.getName() << endl;
}

void Hand::draw(Deck& deck) {                                                                                           //Draw (RNG)
    cards.push_back(deck.draw());
    cout << player << " has drawn " << cards.back().getName() << endl;
}

void Hand::showHand() const {                                                                                           //Reveals hand content
    cout << player << "'s hand" << endl;
    if (cards.empty()) {
        cout << player << "'s hand is empty" << endl;
        return;
    }
    for (const auto& card : cards) {
        cout << card.getName() << endl;
    }
}

bool Hand::isEmpty() const {
    return cards.empty();
}

void Hand::play(Deck& deck, const string& cardName) {                                                                   //Plays a card
    if (isEmpty()) {                                                                                                    //Checks if hand is empty
        cout << player << "'s hand is empty" << endl;
        return;
    }

    auto it = find_if(cards.begin(), cards.end(),                                     //Locates the played card
    [&](const Card& c) { return c.getName() == cardName; });

    if (it == cards.end()) {                                                                                            //If played card is not found in hand
        cout << player << " does not have " << cardName << endl;
        return;
    }

    Card used = *it;
    cout << player << " has played " << used.getName() << "!" << endl;
    used.order();                                                                                                       //Sends the card to order list (placeholder for now)

    cards.erase(it);                                                                                                 //Removes from hand

    deck.addCard(used);                                                                                              //Returns the card back to the deck
    cout << used.getName() << " goes back into the deck." << endl;
}

//Testing function
void testCards() {
    Hand hand("JOHN");

    Card bomb("Bomb");
    Card airlift("Airlift");
    Card reinforcement("Reinforcement");
    Card blockade("Blockade");
    Card diplomacy("Diplomacy");

    Deck emptyDeck({});
    emptyDeck.showDeck();

    Deck deck({bomb, airlift, reinforcement, blockade, diplomacy,
        bomb, airlift, reinforcement, blockade, diplomacy,
        bomb, airlift, reinforcement, blockade, diplomacy,
        bomb, airlift, reinforcement, blockade, diplomacy,
        bomb, airlift, reinforcement, blockade, diplomacy});

    hand.play(deck, "Bomb");

    hand.draw(deck);

    hand.play(deck, "Bomb");
    hand.play(deck, "Bomb");
    hand.play(deck, "Bomb");

    cout << endl << endl;
    hand.addCard(bomb);
    hand.showHand();
    deck.showDeck();

    cout << endl << endl;
    hand.play(deck, "Bomb");
    deck.showDeck();
    hand.showHand();

    cout << endl << endl;
    hand.draw(deck);
    hand.showHand();
    deck.showDeck();

    cout << endl << endl;
    hand.draw(deck);
    hand.showHand();
    deck.showDeck();
}
