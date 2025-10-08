#include "Orders.h"
#include "../Player/Player.h"
#include "../part1-map/Map.h"
#include "../Part-4-Deck/Cards.h"
#include <string>

void testOrdersLists(){
    cout << "-----------------------------------------------------------------------" << endl;
    cout << "ORDERS LIST TEST" << endl;

    std::vector<std::string> adj(5);
    Continent* c1 = new Continent("NA", 5);
    std::string name1 = "Montreal";
    std::string name2 = "Toronto";
    std::string name3 = "Miami";
    std::string name4 = "Talahasee";

    Territory* t1 = new Territory(name1, c1, 1, 3, adj);
    Territory* t2 = new Territory(name2, c1, 2, 4, adj);
    Territory* t3 = new Territory(name3, c1, 5, 6, adj);
    Territory* t4 = new Territory(name4, c1, 7 ,8, adj);

    Player* p1 = new Player("Shawn");
    //p1->getTerritories().push_back(t1);
    //p1->getTerritories().push_back(t2);
    p1->addTerritory(t1);
    p1->addTerritory(t2);

    Player* p2 = new Player("Howard");
    //p2->getTerritories().push_back(t3);
    //p2->getTerritories().push_back(t4);
    p2->addTerritory(t3);
    p2->addTerritory(t4);


    cout << "VALID ORDERS" << endl;

    cout << p1->getTerritories().size() << endl;

    Orders* vorder1 = new OrdersDeploy(p1, p1->getTerritories()[0], 3);
    Orders* vorder2 = new OrdersAdvance(p1, p1->getTerritories()[0], p1->getTerritories()[1], 1);
    Orders* vorder3 = new OrdersBomb(p1, p2->getTerritories()[0]);
    Orders* vorder4 = new OrdersBlockade(p1, p1->getTerritories()[1]);
    Orders* vorder5 = new OrdersAirlift(p1, p1->getTerritories()[0], p1->getTerritories()[1], 2);
    Orders* vorder6 = new OrdersNegotiate(p1, p2);
    Orders* vlist[6] = {vorder1, vorder2, vorder3, vorder4, vorder5, vorder6};

    // cout << "INVALID ORDERS" << endl;
    Orders* iorder1 = new OrdersDeploy(p2, p1->getTerritories()[0], 3);
    Orders* iorder2 = new OrdersAdvance(p2, p1->getTerritories()[1], p2->getTerritories()[0], 10);
    Orders* iorder3 = new OrdersBomb(p2, p2->getTerritories()[0]);
    Orders* iorder4 = new OrdersBlockade(p2, p1->getTerritories()[1]);
    Orders* iorder5 = new OrdersAirlift(p2, p1->getTerritories()[0], p2->getTerritories()[0], 10);
    Orders* iorder6 = new OrdersNegotiate(p2, p2);

    Orders* ilist[6] = {iorder1, iorder2, iorder3, iorder4, iorder5, iorder6};



    for (int n = 0; n < 6; n++){
        p1->getOrderList()->add(vlist[n]);
        p2->getOrderList()->add(ilist[n]);
    }

    cout << "BELOW IS THE LIST OF ORDERS FOR PLAYER ONE (VALID)\n" << endl;
    cout << *(p1->getOrderList()) << endl;
    cout << "\nBELOW IS THE LIST OF ORDERS FOR PLAYER 1 (INVALID)\n" << endl;
    cout << *(p2->getOrderList()) << endl;

    // cout << "NOW PRINTING THE VALIDITY OF THE ORDERS\n" << endl;
    cout << "PLAYER 1 ORDERS" << endl;
    for (auto order : p1->getOrderList()->getList()){
        cout << "IS VALID?: ";
        order->validate();
        cout << endl;
    }

    cout << "\nPLAYER 2 ORDERS" << endl;
    for (auto order : p2->getOrderList()->getList()){
        cout << "IS VALID?: ";
        order->validate();
        cout << endl;
    }


    int firstInex, secondIndex;
    int indexCount = 0;
    cout << "PLEASE ENTER WHICH INDEX YOU WANT TO MOVE AND WHERE YOU WANT TO MOVE IT:" << endl;
    for (auto order : p1->getOrderList()->getList()){
        cout << indexCount << ": " << *order << endl;
        indexCount++;
    }
    cin >> firstInex >> secondIndex;

    cout << "LIST BEFORE MOVE\n" << *(p1->getOrderList()) << endl;
    p1->getOrderList()->move(firstInex, secondIndex);
    cout << "LIST AFTER MOVE\n" << *(p1->getOrderList());



    indexCount = 0;
    cout << "\nPLEASE ENTER WHICH INDEX YOU WANT TO REMOVE:" << endl;
    for (auto order : p1->getOrderList()->getList()){
        cout << indexCount << ": " << *order << endl;
        indexCount++;
    }
    cin >> firstInex;

    cout << "LIST BEFORE REMOVE\n" << *(p1->getOrderList()) << endl;
    p1->getOrderList()->remove(firstInex);
    cout << "LIST AFTER REMOVE\n" << *(p1->getOrderList());



    cout << "\nTESTING COPY CONSTRUCTORS, AND ASSIGNMENT OPERATOR OVERLOAD\n" << endl;
    Orders* o1 = new Orders();
    Orders* o2 = new Orders(*o1);
    Orders* o3 = new Orders();
    *o3 = *o1;

    cout << "ORDERS MEMORY ADDRESSES AND DATA:" << endl;
    cout << o1 << ", DATA: " << *o1 << "\n\n";
    cout << o2 << ", DATA: " << *o2 << "\n\n";
    cout << o3 << ", DATA: " << *o3 << "\n\n";

    OrdersAdvance* oa1 = new OrdersAdvance(p1, p1->getTerritories()[0], p1->getTerritories()[1], 1);
    OrdersAdvance* oa2 = new OrdersAdvance(*oa1);
    // OrdersAdvance* oa3 = new OrdersAdvance();
    // *oa3 = *oa1;

    // cout << "ORDERS ADVANCE MEMORY ADDRESSES AND DATA:" << endl;
    // cout << oa1 << ", DATA: " << *oa1 << "\n\n";
    // cout << oa2 << ", DATA: " << *oa2 << "\n\n";
    // cout << oa3 << ", DATA: " << *oa3 << "\n\n";



    // OrdersList* olist1 = new OrdersList(*(p1->getOrderList()));
    // OrdersList* olist2 = new OrdersList();
    // *olist2 = *olist1;

    // cout << "\nORDER LIST MEMORY ADDESES AND DATA:" << endl;
    // cout << p1->getOrderList() << ", DATA: " << *(p1->getOrderList()) << "\n\n";
    // cout << olist1 << ", DATA: " << *olist1 << "\n\n";
    // cout << olist2 << ", DATA: " << *olist2 << "\n\n";

    // Player* p3 = new Player("Negin");
    // cout << "\nTESTING IHERITED CONSTRUCTOR" << endl;
    // OrdersBomb* b1 = new OrdersBomb(p3, new Territory("Hogwarts", c1, 5, 8, adj));
    // OrdersBomb* b2 = new OrdersBomb(*b1);
    // OrdersBomb* b3 = new OrdersBomb();
    // *b3 = *b1;

    // cout << "BOMB ADDRESSES" << endl;
    // cout << b1 << ": " << *b1 << endl;
    // cout << b2 << ": " << *b2 << endl;
    // cout << b3 << ": " << *b3 << endl;

    cout << "-----------------------------------------------------------------------" << endl;
}


// int main(){

//     testOrdersLists();
    
//     // Player* p1 = new Player(1);
//     // Player* p2 = new Player(2);
//     // Territory* t1 = new Territory("Canada", 3, p1);
//     // Orders* o1 = new Orders(p1, t1);

//     // cout << "\nPlayer: " << p1 << " DATA: " << *p1 << endl;
//     // cout << "\nTerritory: " << t1 << " DATA: " << *t1 << endl;
//     // cout << "\nOrders: " << o1 << " DATA: " << *o1 << "\n" << endl;

//     // delete o1;

//     // cout << "\nPlayer: " << p1 << " DATA: " << *p1 << endl;
//     // cout << "\nTerritory: " << t1 << " DATA: " << *t1 << endl;
//     //cout << "\nOrders: " << o1 << " DATA: " << *o1 << endl;

//     return 0;
// }