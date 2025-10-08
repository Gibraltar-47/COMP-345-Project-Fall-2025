//
// Created by ngyna on 2025-09-28.
//testing file
#include "Player.h"
#include "Orders.h"

#include <iostream>
#include <vector>
using namespace std;
/**
void testPlayers(){
//create players
 Player p1("Jack");
 Player p2("Alyssa");
//create territories
 Territory* tr1 = new Territory();
 Territory* tr2 = new Territory();
//assign terr to players
p1.addTerritory(tr1);
p1.addTerritory(tr2);
p2.addTerritory(tr1);
//print player status
 cout<<p1<<endl;

 cout<<p2<<endl;
//add cards

 Card* c1 = new Card("Fly");
 Card* c2 = new Card("Camp");

 p1.addCard(c1);
p1.addCard(c2);
//issue orders
p1.issueOrder();
p2.issueOrder();

 cout<< endl;
cout<<p1<<endl;

cout<<p2<<endl;
//delete to avoid memory leaks
//delete tr1;
//delete tr2;

p1.addOrder(new OrdersBlockade);

p1.issueOrder();

}*/
void test() {
    cout << endl;
    cout << endl;
    cout << endl;
    cout << endl;
    cout << endl;
    cout << endl;
 Continent* north = new Continent("North", 5);
    Continent* south = new Continent("South", 3);

    Territory* t1 = new Territory("Canada", north, 0, 0, {});
    Territory* t2 = new Territory("USA", north, 1, 0, {"Canada"});
    Territory* t3 = new Territory("Mexico", south, 2, 0, {"USA"});

    north->addTerritory(t1);
    north->addTerritory(t2);
    south->addTerritory(t3);

    Map world("Earth");
    world.addContinent(north);
    world.addContinent(south);
    world.addTerritory(t1);
    world.addTerritory(t2);
    world.addTerritory(t3);

    cout << "Map initialized: " << world.getName() << endl;

    // --- Create players ---
    Player* p1 = new Player("Alice");
    Player* p2 = new Player("Bob");

    cout << "Players created: " << p1->getName() << ", " << p2->getName() << endl;

    // --- Assign territories ---
    p1->addTerritory(t1);
    p1->addTerritory(t2);
    p2->addTerritory(t3);

    cout << "Alice owns: " << endl;
    p1->printStatus();
    cout << "Bob owns: " << endl;
    p2->printStatus();

    // --- Create a deck and cards ---
    Deck deck;
    deck.addCard(new Card("Bomb"));
    deck.addCard(new Card("Airlift"));
    deck.addCard(new Card("Reinforcement"));
    deck.addCard(new Card("Blockade"));

    cout << "\nDeck size: " << deck.getDeckSize() << endl;

    Hand* hand1 = new Hand(p1->getName());
    hand1->draw(deck);
    hand1->draw(deck);

    //cout << "\n" << p1->getName() << "'s hand:" << endl;
    cout << *hand1 << endl;

    // --- Play a card to create an order ---
    OrdersList olist;
    hand1->playCard(deck, "Bomb", olist);
    hand1->playCard(deck, "Airlift", olist);

    cout << "\nOrders after playing cards:" << endl;
    //olist.resolveOrder();

    // --- Add manual order ---
    OrdersDeploy* deployOrder = new OrdersDeploy(p1, t1, 10);
    //olist.addOrder(reinterpret_cast<Order*>(deployOrder));

    cout << "\nManual deploy order added. Orders executing:" << endl;
    //olist.resolveOrder();

    // --- Clean up ---
    delete p1;
    delete p2;
    delete hand1;
}

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
    cout << deck << endl;

    OrdersList olist;

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
void testLoadMap()
{
    MapLoader mapLoader;

    cout<<"TESTING THE LOADMAP() AND VALIDATE() FUNCTIONS ON VALID MAP FILE : Antarctica.map & Annys Piratenwelt.map"<<endl<<"IF MAP IS VALID, A CONFIRMATION WILL BE PRINTED IN CONSOLE AND THE MAP OBJ WILL BE PRINTED"<<endl<<endl;
    Map map1=mapLoader.loadMap("../Code/mapFiles/Antarctica.map");
    if (map1.validate())
    {
        cout<<std::endl<<"Map "<<map1.getName()<<" was validated and will now be printed below!"<<std::endl<<std::endl<<map1<<endl;
    }

    Map map2=mapLoader.loadMap("../Code/mapFiles/Annys Piratenwelt.map");
    if (map2.validate())
    {
        cout<<std::endl<<"Map "<<map2.getName()<<" was validated and will now be printed below!"<<std::endl<<std::endl<<map2<<endl;
    }
    /**
    cout<<"TESTING THE LOADMAP() AND VALIDATE() FUNCTIONS ON INVALID FILE : fakeFile.txt"<<endl<<"IF MAP IS VALID, A CONFIRMATION WILL BE PRINTED IN CONSOLE AND THE MAP OBJ WILL BE PRINTED"<<endl<<endl;
    Map map3=mapLoader.loadMap("../mapFiles/fakeFile.txt");
    if (map3.validate()){
        cout<<std::endl<<"Map "<<map3.getName()<<" was validated and will now be printed below!"<<std::endl<<std::endl<<map3<<endl;
    }
    */

    cout<<endl<<endl<<"TESTING THE VALIDATE() & COPY CONSTRUCTOR AND ASSIGNMENT OPERATION & DESTRUCTOR FUNCTIONS ON MAP OBJECT "<<endl<<"(MAP is connected but the territories don't have a continent)"<<endl<<"IF MAP IS VALID, A CONFIRMATION WILL BE PRINTED IN CONSOLE AND THE MAP OBJ WILL BE PRINTED"<<endl<<endl;

    Map map4("West Island");

    auto* terr1 = new Territory("Pointe-Claire", nullptr, 0, 1, {"Kirkland"});

    map4.addTerritory(terr1);

    Territory terr2("Kirkland",nullptr,0,1,{"Pointe-Claire"});
    //proof of deep copy working
    *terr1=terr2;

    map4.addTerritory(terr1);

    if (map4.validate())
    {
        cout<<std::endl<<"Map "<<map4.getName()<<" was validated and will now be printed below!"<<std::endl<<std::endl<<map4<<endl;
    }else cout<<std::endl<<"Map "<<map4.getName()<<" was NOT validated!"<<std::endl<<std::endl<<map4<<endl;

    cout<<endl<<endl<<"TESTING THE VALIDATE() & COPY CONSTRUCTOR AND ASSIGNMENT OPERATION & DESTRUCTOR FUNCTIONS ON MAP OBJECT "<<endl<<"(MAP is connected but the territories don't have a continent)"<<endl<<"IF MAP IS VALID, A CONFIRMATION WILL BE PRINTED IN CONSOLE AND THE MAP OBJ WILL BE PRINTED"<<endl<<endl;

    Map map5("West Island");

    auto* continent1= new Continent("Montreal",3);
    Continent continent2("Dorval",2);
    *continent1=continent2;
    map5.addContinent(continent1);
    terr1->setContinent(map5.getContinent("Dorval"));
    map5.addTerritory(terr1);
    map5.getContinent("Dorval")->addTerritory(map5.getTerritory("Kirkland"));

    Territory terr3("Pointe-Claire", map5.getContinent("Dorval"), 0, 1, {"Kirkland"});

    *terr1=terr3;
    map5.addTerritory(terr1);
    map5.getContinent("Dorval")->addTerritory(map5.getTerritory("Pointe-Claire"));

    map5.initAdjMatrix();
    vector<string>adjTerrName;
    for (Continent* c:map5.getContinents()){
        c->initAdjMatrix();
        for (Territory* t:c->getTerritories()){
            adjTerrName.push_back(t->getName());
            for (const string& name:t->getAdjTerritoriesNames()){
                Territory* terr=map5.getTerritory(name);
                if (terr!=nullptr&&terr->getContinent()==c&&!c->isConnected(t,map5.getTerritory(name))){                 //3 checks: 1. is the destination territory pointer null 2. is the destination territory in the same continent as its source
                    c->setVertice(t,map5.getTerritory(name));                                                            //3. was the vertice between the 2 territories already created
                }
            }
        }
    }
    adjTerrName.clear();
    //populate the adjacency matrix for the map
    for (Territory* t:map5.getTerritories()){
        adjTerrName.push_back(t->getName());
        for (const string& name:t->getAdjTerritoriesNames()){
            Territory* terr=map5.getTerritory(name);
            if (terr!=nullptr&&!map5.isConnected(t,map5.getTerritory(name))){
                map5.setVertice(t,map5.getTerritory(name));
            }
        }
    }

    if (map5.validate()){
        cout<<std::endl<<"Map "<<map5.getName()<<" was validated and will now be printed below!"<<std::endl<<std::endl<<map5<<endl;
    }

    cout<<"Here is example of a stream insertion for a continent : "<<endl<<endl<<*map5.getContinent("Dorval")<<endl;

    cout<<"Here is example of a stream insertion for a territory : "<<endl<<endl<<*map5.getTerritory("Kirkland")<<endl;

    cout<<"Here is example of a stream insertion for a map loader : "<<endl<<endl<<mapLoader<<endl;

    delete continent1;
    delete terr1;
}
void testOrdersLists(){
    cout << "-----------------------------------------------------------------------" << endl;
    cout << "ORDERS LIST TEST" << endl;

    Continent* c1 = new Continent("North", 5);
    Continent* c2 = new Continent("South", 5);

    Player* p1 = new Player("John");
    Territory* montreal = new Territory("Montreal", c1, 0, 0, {});
    Territory* toronto = new Territory("Toronto", c1, 1, 1, {});

    Player* p2 = new Player("Joseph");
    Territory* miami = new Territory("Miami", c2, 2, 2, {});
    Territory* tallahassee = new Territory("Tallahassee", c2, 3, 3, {});

    p1->territories.push_back(montreal);
    p1->territories.push_back(toronto);

    p2->territories.push_back(tallahassee);
    p2->territories.push_back(miami);


    // cout << "VALID ORDERS" << endl;
    Orders* vorder1 = new OrdersDeploy(p1, p1->territories[0], 3);
    Orders* vorder2 = new OrdersAdvance(p1, p1->territories[0], p1->territories[1], 1);
    Orders* vorder3 = new OrdersBomb(p1, p2->territories[0]);
    Orders* vorder4 = new OrdersBlockade(p1, p1->territories[1]);
    Orders* vorder5 = new OrdersAirlift(p1, p1->territories[0], p1->territories[1], 2);
    Orders* vorder6 = new OrdersNegotiate(p1, p2);
    Orders* vlist[6] = {vorder1, vorder2, vorder3, vorder4, vorder5, vorder6};

    // cout << "INVALID ORDERS" << endl;
    Orders* iorder1 = new OrdersDeploy(p2, p1->territories[0], 3);
    Orders* iorder2 = new OrdersAdvance(p2, p1->territories[1], p2->territories[0], 10);
    Orders* iorder3 = new OrdersBomb(p2, p2->territories[0]);
    Orders* iorder4 = new OrdersBlockade(p2, p1->territories[1]);
    Orders* iorder5 = new OrdersAirlift(p2, p1->territories[0], p2->territories[0], 10);
    Orders* iorder6 = new OrdersNegotiate(p2, p2);

    Orders* ilist[6] = {iorder1, iorder2, iorder3, iorder4, iorder5, iorder6};



    for (int n = 0; n < 6; n++){
        p1->ordersList->add(vlist[n]);
        p2->ordersList->add(ilist[n]);
    }

    cout << "BELOW IS THE LIST OF ORDERS FOR PLAYER ONE (VALID)\n" << endl;
    cout << *(p1->ordersList) << endl;
    cout << "\nBELOW IS THE LIST OF ORDERS FOR PLAYER 1 (INVALID)\n" << endl;
    cout << *(p2->ordersList) << endl;

    cout << "NOW PRINTING THE VALIDITY OF THE ORDERS\n" << endl;
    cout << "PLAYER 1 ORDERS" << endl;
    for (auto order : p1->ordersList->getList()){
        cout << "IS VALID?: ";
        order->validate();
        cout << endl;
    }

    cout << "\nPLAYER 2 ORDERS" << endl;
    for (auto order : p2->ordersList->getList()){
        cout << "IS VALID?: ";
        order->validate();
        cout << endl;
    }


    int firstInex, secondIndex;
    int indexCount = 0;
    cout << "PLEASE ENTER WHICH INDEX YOU WANT TO MOVE AND WHERE YOU WANT TO MOVE IT:" << endl;
    for (auto order : p1->ordersList->getList()){
        cout << indexCount << ": " << *order << endl;
        indexCount++;
    }
    cin >> firstInex >> secondIndex;

    cout << "LIST BEFORE MOVE\n" << *(p1->ordersList) << endl;
    p1->ordersList->move(firstInex, secondIndex);
    cout << "LIST AFTER MOVE\n" << *(p1->ordersList);



    indexCount = 0;
    cout << "\nPLEASE ENTER WHICH INDEX YOU WANT TO REMOVE:" << endl;
    for (auto order : p1->ordersList->getList()){
        cout << indexCount << ": " << *order << endl;
        indexCount++;
    }
    cin >> firstInex;

    cout << "LIST BEFORE REMOVE\n" << *(p1->ordersList) << endl;
    p1->ordersList->remove(firstInex);
    cout << "LIST AFTER REMOVE\n" << *(p1->ordersList);



    cout << "\nTESTING COPY CONSTRUCTORS, AND ASSIGNMENT OPERATOR OVERLOAD\n" << endl;
    Orders* o1 = new Orders();
    Orders* o2 = new Orders(*o1);
    Orders* o3 = new Orders();
    *o3 = *o1;

    cout << "ORDERS MEMORY ADDRESSES AND DATA:" << endl;
    cout << o1 << ", DATA: " << *o1 << "\n\n";
    cout << o2 << ", DATA: " << *o2 << "\n\n";
    cout << o3 << ", DATA: " << *o3 << "\n\n";

    OrdersAdvance* oa1 = new OrdersAdvance(p1, p1->territories[0], p1->territories[1], 1);
    OrdersAdvance* oa2 = new OrdersAdvance(*oa1);
    OrdersAdvance* oa3 = new OrdersAdvance();
    *oa3 = *oa1;

    cout << "ORDERS ADVANCE MEMORY ADDRESSES AND DATA:" << endl;
    cout << oa1 << ", DATA: " << *oa1 << "\n\n";
    cout << oa2 << ", DATA: " << *oa2 << "\n\n";
    cout << oa3 << ", DATA: " << *oa3 << "\n\n";



    OrdersList* olist1 = new OrdersList(*(p1->ordersList));
    OrdersList* olist2 = new OrdersList();
    *olist2 = *olist1;

    cout << "\nORDER LIST MEMORY ADDESES AND DATA:" << endl;
    cout << p1->ordersList << ", DATA: " << *(p1->ordersList) << "\n\n";
    cout << olist1 << ", DATA: " << *olist1 << "\n\n";
    cout << olist2 << ", DATA: " << *olist2 << "\n\n";

    Player* p3 = new Player("Jonathan");
    cout << "\nTESTING IHERITED CONSTRUCTOR" << endl;

    Continent* magic = new Continent("Magic", 1);
    Territory* hogwarts = new Territory("Hogwarts", magic, 4, 4, {});

    OrdersBomb* b1 = new OrdersBomb(p3, hogwarts);
    OrdersBomb* b2 = new OrdersBomb(*b1);
    OrdersBomb* b3 = new OrdersBomb();
    *b3 = *b1;

    cout << "BOMB ADDRESSES" << endl;
    cout << b1 << ": " << *b1 << endl;
    cout << b2 << ": " << *b2 << endl;
    cout << b3 << ": " << *b3 << endl;

    cout << "-----------------------------------------------------------------------" << endl;
}

 int main(){
    testCards();

    test();
    cout <<endl;
    cout <<endl;
    cout <<endl;
    cout <<endl;
    cout <<endl;
    cout <<endl;

    cout <<endl;
    cout <<endl;
    cout <<endl;

    testLoadMap();

    testOrdersLists(); //needs tweaking <=============
 return 0;
 }

