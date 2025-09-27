//
// Created by Howard on 2025-09-21.
//

#ifndef CLIONPROJECTS_DECK_H
#define CLIONPROJECTS_DECK_H

#include <string>
#include <vector>

using namespace std;

class Card {
    private:
        string name;  //Name of card

    public:
        Card(string name);

        string getName() const;

        void order();

};

class Deck {
    private:
        vector<Card> cards;  //Deck content

    public:
        Deck(vector<Card> cards);

        void addCard(Card card);

        void showDeck() const;

        int getDeckSize() const;

        Card draw();

        bool isEmpty() const;

};

class Hand {
    private:
        string player;    //Player name

        vector<Card> cards;  //Player hand

    public:
        Hand(string name);

        void addCard(const Card& card);

        void showHand() const;

        void draw(Deck& deck);

        void play(Deck& deck, const string& cardName);

        bool isEmpty() const;
};


void testCards();
#endif //CLIONPROJECTS_DECK_H