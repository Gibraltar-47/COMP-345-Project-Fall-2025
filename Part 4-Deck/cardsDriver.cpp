#include "Cards.h"
#include <string>
#include <iostream>
#include <random>


using namespace std;

//Testing function
void testCards() {

    Deck deck;

    //Add 7 copies of each card type
    vector<string> cardNames = {"Bomb", "Airlift", "Blockade", "Diplomacy", "Blockade"};
    for (const auto& name : cardNames) {
        for (int i = 0; i < 7; ++i) {
            deck.addCard(new Card(name));
        }
    }

    cout << "Deck created and 7 copies of each card added (" << cardNames.size() * 7 << " total)." << endl << endl;

    OrderList olist;

    Hand player1("Tester1");
    Hand player2("Tester2");
    cout << "Two player hands created." << endl;

    //Each player draws 6 cards Draw() test
    cout << endl;
    for (int i = 0; i < 6; ++i) {
        player1.draw(deck);
        player2.draw(deck);
    }

    cout << endl;
    cout << player1 << endl;
    cout << player2 << endl;

    //Each plays one card Play() test
    player1.playCard(deck, "Bomb", olist);
    player2.playCard(deck, "Airlift", olist);

    cout << endl;
    cout << player1 << endl;
    cout << player2 << endl;

    cout << "\nBoth players played one card each.\n" << endl;
    cout << "Deck now: " << deck << endl;

    //Player2 tries to play a nonexistent card
    cout << endl;
    cout << "Tester2 tries to play a nonexistent card 'Fly':" << endl;
    player2.playCard(deck, "Fly", olist);

    cout << endl;
    cout << player1 << endl;
    cout << player2 << endl;

    cout << endl;
    cout << "Deck state after invalid play attempt:" << endl;
    cout << deck << endl;

    //Test copy constructor here
    cout << endl;
    cout << "Copy Constructor Test" << endl;
    Hand cloneHand(player1);
    cout << "Original Hand: " << player1 << endl;
    cout << "Cloned Hand:   " << cloneHand << endl;

    //Play a card from the original hand to see if it affects the copy
    player1.playCard(deck, "Blockade", olist);

    cout << endl;
    cout << "After playing from original:" << endl;
    cout << "Original Hand: " << player1 << endl;
    cout << "Cloned Hand:   " << cloneHand << endl;

    //Return all cards
    player1.returnAll(deck);
    player2.returnAll(deck);
    cloneHand.returnAll(deck);

    cout << "\nAll cards returned to deck.\n" << endl;
    cout << "Deck now: " << deck << endl;
}


int main() {

    testCards();

    return 0;
}