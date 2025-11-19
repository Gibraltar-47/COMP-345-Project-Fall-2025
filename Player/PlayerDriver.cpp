//
// Created by ngyna on 2025-09-28.
//testing file
#include "Player.h"
#include "../Orders/Orders.h"
#include "../part1-map/Map.h"
#include "../Part-4-Deck/Cards.h"
#include "PlayerStrategy.h"

#include <iostream>
#include <vector>
using namespace std;

void testPlayers(){
    std::vector<std::string> adj(5);
    Continent* con1 = new Continent("NA", 5);
    std::string name1 = "Montreal";
    std::string name2 = "Toronto";


    Territory* tr1 = new Territory(name1, con1, 1, 3, adj);
    Territory* tr2 = new Territory(name2, con1, 2, 4, adj);




//create players
 Player p1("Jack");
 Player p2("Alyssa");

//assign terr to players
p1.addTerritory(tr1);
p1.addTerritory(tr2);
p2.addTerritory(tr1);
//print player status
p1.printStatus();
p2.printStatus();
//add cards
 Card* c1 = new Card();
 Card* c2 = new Card();

 p1.addCard(c1);
p1.addCard(c2);
//issue orders
//p1.issueOrder();
//p2.issueOrder();
cout<<p1<<endl;
cout<<p2<<endl;

//delete to avoid memory leaks
delete tr1;
delete tr2;

cout << "END OF PLAYER DRIVER" << endl;
}

