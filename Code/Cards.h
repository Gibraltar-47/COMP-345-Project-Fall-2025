//
// Created by Howard on 2025-09-21.
//

#ifndef CLIONPROJECTS_DECK_H
#define CLIONPROJECTS_DECK_H

#include <string>
#include <vector>


class Card {
    //The Card class is being used by both the Hand class and the Deck class
    private:
        std::string* name;  //Name of card

    public:
        Card();
        Card(const std::string& name);
        Card(const Card& other);
        Card& operator=(const Card& other);
        ~Card();

        std::string getName() const;
        void setName(const std::string& n);

        void order() const; //Placeholder as of now

        friend std::ostream& operator<<(std::ostream& os, const Card& c);
};

class Deck {
    //The deck class owns all the card objects. (deep copy)
    private:
    std::vector<Card*> cards;  //Deck content

    public:
        Deck();
        Deck(const std::vector<Card *> &cards);
        Deck(const Deck& other);
        Deck& operator=(const Deck& other);
        ~Deck();

        int getDeckSize() const;

        void addCard(Card* card);
        Card* draw();


        bool isEmpty() const;
        friend std::ostream& operator<<(std::ostream& os, const Deck& d);

};

class Hand {
    //The hand class only borrows cards from the deck (shallow copy)
    private:
        std::string* player;    //Player name (currently a placeholder)

        std::vector<Card*> cards;  //Player hand

    public:
        Hand();
        Hand(const std::string& name);
        Hand(const Hand& other); //It is here for the instructions, but a Hand should not be replicated since it is unique to every player.
        ~Hand();
        Hand& operator=(const Hand& other);

        void addCard(Card* card);

        void draw(Deck& deck);

        void play(Deck& deck, const std::string& cardName);

        void returnAll(Deck& deck);

        bool isEmpty() const;

        friend std::ostream& operator<<(std::ostream& os, const Hand& hand);
};
#endif //CLIONPROJECTS_DECK_H