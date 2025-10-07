#include "Cards.h"
#include <string>
#include <iostream>
#include <random>


using namespace std;

//Testing function
void testCards() {
    cout << "=== BEGIN TEST ===" << endl;
        Deck deck;

        // Add 7 copies of each card type
        vector<string> cardNames = {"Bomb", "Airlift", "Blockade", "Diplomacy", "Blockade"};
        for (const auto& name : cardNames) {
            for (int i = 0; i < 7; ++i) {
                deck.addCard(new Card(name));
            }
        }

        cout << "Deck created and 7 copies of each card added ("
             << cardNames.size() * 7 << " total)." << endl << endl;

        OrderList olist;

        Hand player1("Tester1");
        Hand player2("Tester2");
        cout << "Two player hands created.\n" << endl;

        // Each player draws 3 cards
        for (int i = 0; i < 3; ++i) {
            player1.draw(deck);
            player2.draw(deck);
        }

        cout << "\n" << player1 << endl;
        cout << player2 << endl;

        // Each plays one card
        player1.playCard(deck, "Bomb", olist);
        player2.playCard(deck, "Airlift", olist);

        cout << "\n" << player1 << endl;
        cout << player2 << endl;

        cout << "\nBoth players played one card each.\n" << endl;
        cout << "Deck now: " << deck << endl;

        // Player2 tries to play a nonexistent card
        cout << "\nTester2 tries to play a nonexistent card 'Fly':" << endl;
        player2.playCard(deck, "Fly", olist);

        cout << "\n" << player1 << endl;
        cout << player2 << endl;

        cout << "\nDeck state after invalid play attempt:" << endl;
        cout << deck << endl;

        //  Test copy constructor here
        cout << "\n=== Copy Constructor Test ===" << endl;
        Hand cloneHand(player1);
        cout << "Original Hand: " << player1 << endl;
        cout << "Cloned Hand:   " << cloneHand << endl;

        // Play a card from the original hand to see if it affects the copy
        player1.playCard(deck, "Blockade", olist);

        cout << "\nAfter playing from original:" << endl;
        cout << "Original Hand: " << player1 << endl;
        cout << "Cloned Hand:   " << cloneHand << endl;

        // Return all cards
        player1.returnAll(deck);
        player2.returnAll(deck);
        cloneHand.returnAll(deck);

        cout << "\nAll cards returned to deck.\n" << endl;
        cout << "Deck now: " << deck << endl;

        cout << "\n=== END OF SCOPE ===" << endl;

}


int main() {

    testCards();


    return 0;
}