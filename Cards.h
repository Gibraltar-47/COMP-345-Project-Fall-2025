//
// Created by Howard on 2025-09-21.
//

#ifndef CLIONPROJECTS_DECK_H
#define CLIONPROJECTS_DECK_H

#include <string>
#include <vector>



class Card {
    private:
        std::string name;  //Name of card

    public:
        Card(std::string name);

        std::string getName() const;

        void order();

};

class Deck {
    private:
        std::vector<Card> cards;  //Deck content

    public:
        Deck(std::vector<Card> cards);

        void addCard(Card card);

        void showDeck() const;

        int getDeckSize() const;

        Card draw();

        bool isEmpty() const;

};

class Hand {
    private:
        std::string player;    //Player name

        std::vector<Card> cards;  //Player hand

    public:
        Hand(std::string name);

        void addCard(const Card& card);

        void showHand() const;

        void draw(Deck& deck);

        void play(Deck& deck, const std::string& cardName);

        bool isEmpty() const;
};


void testCards();
#endif //CLIONPROJECTS_DECK_H