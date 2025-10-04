#include "Cards.h"
#include <string>
#include <iostream>
#include <random>


using namespace std;

//Testing function
void testCards() {
    vector<string> cardNames = {"Bomb", "Airlift", "Diplomacy", "Reinforcement", "Blockade"};

    cout << "Deck has been created." << endl;
    Deck deck;
    for (const auto& name : cardNames) { // Add 6 copies of each card
        for (int i = 0; i < 6; i++) {
            deck.addCard(new Card(name));
        }
    }

    cout << deck << endl;
    cout << endl;
    Hand player1("John");                          //Player creation
    Hand player2("Robert");

    cout << "Playing an empty hand" << endl;
    player1.play(deck, "Flashcard"); //plays empty card

    cout << endl;
    cout << "Drawing Cards :" << endl;
    for (int i = 0; i < 5; i++) {                         //Fills hand
        player1.draw(deck);
        player2.draw(deck);
    }
    cout << endl;
    cout << deck << endl;                                  //deck content

    cout << endl;                                           //player hand content
    cout << player1 << endl;
    cout << player2 << endl;

    cout << endl;

    cout << endl;                                   //attempts to play a card
    player1.play(deck,"Bomb");
    cout << deck << endl;

    cout << endl;
    player2.play(deck,"Airlift");
    cout << deck << endl;

    cout << endl;
    player1.play(deck,"Reinforcement");
    cout << deck << endl;

    cout << endl;
    player2.play(deck,"Blockade");
    cout << deck << endl;

    cout << endl;                          //plays non existent card
    player1.play(deck,"BlankCard");
    cout << endl;


    Hand player3(player1);


    cout << "testing copy constructor" << endl;
    cout << player1 << endl;
    cout << player3 << endl;


    cout << endl;

    player1.play(deck,"Reinforcement");
    player1.play(deck,"Blockade");
    player1.play(deck,"Airlift");

    cout << deck << endl;
    cout << player1 << endl;
    cout << player3 << endl;

    cout << endl;
    player1.returnAll(deck);
    cout<< player1 << endl;
    cout << player2 << endl;
    cout << player3 << endl;
    cout << deck << endl;

    cout << "Deleting John" << endl;
    player1.returnAll(deck);
    player1.~Hand();



}

int main() {
    testCards();

    return 0;
}