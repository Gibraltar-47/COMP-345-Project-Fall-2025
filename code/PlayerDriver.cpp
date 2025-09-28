//
// Created by ngyna on 2025-09-28.
//testing file
#include "Player.h"

void testPlayers(){
 std::cout<<"Testing Player Class: "<< std::endl;
 Player p1("Jack");
 Player p2("Alyssa");
 Territory tr1("North"), tr2("West");
 Card cr1("Bomb");
 std::cout<<"Created players: "<<p1.getName()<<" and "<<p2.getName()<<std::endl;
 //adding cards, orders and territories
 p1.addTerritory(&tr1);
 p2.addTerritory(&tr2);
 p1.addCard(&ca1);
 p2.addCard(&ca2);
 p1.addOrder("Attack South");
 auto defendList=p1.toDefend();
 auto attackList=p1.toAttack();
 std::cout<<p1.getName()<<" has "<<defendList.size()<<" territories to defend."<< std::endl;
 std::cout<<p1.getName()<<" has "<<attackList.size()<<" territories to attack"<<std::endl;

}
 int main(){
  testPlayers();
 return 0;
 }

