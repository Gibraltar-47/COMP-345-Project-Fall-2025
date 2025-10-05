#include "Orders.h"

int main(){
    // OrdersList orderList;
    // orderList.getList().push_back(new Orders());

    // for (Orders* order : orderList.getList()) {
    //     cout << order << "\n";
    // }

    // Orders order1;
    // Orders order2 = order1;
    // Orders order3;
    // order3 = order2;

    // Orders* order1 = new Orders();
    // Orders* order2 = new Orders(*order1);
    // Orders* order3 = new Orders();
    // *order3 = *order2;

    // Orders* order1 = new OrdersDeploy();
    // Orders* order2 = new OrdersDeploy(new Territory());
    // Orders* order3 = new OrdersDeploy(dynamic_cast<OrdersDeploy&>(*order1));
    // Orders* order4 = new OrdersDeploy();
    // *order4 = *order2;


    //Orders* order2 = new OrdersDeploy(*order1);


    // cout << "Addresses:\n";
    // cout << order1 << endl;
    // cout << order2 << endl;
    // cout << order3 << endl;
    // cout << order4 << endl;

    // cout << "Data:\n";
    // cout << *order1 << endl;
    // cout << *order2 << endl;
    // cout << *order3 << endl;
    // cout << *order4 << endl;
    // cout << "DONE";

    //Orders* order1 = new OrdersDeploy(new Territory(), 10);
    //cout << static_cast<OrdersDeploy*>(order1)->getNumArmies() << endl;



    // Player* p1 = new Player(1);
    // p1->ownedTerritories.push_back(new Territory("Montreal", 5, p1));
    // p1->ownedTerritories.push_back(new Territory("Toronto", 4, p1));

    // Player* p2 = new Player(2);
    // p2->ownedTerritories.push_back(new Territory("Miami", 6, p2));
    // p2->ownedTerritories.push_back(new Territory("Talahasee", 2, p2));

    // cout << "VALID ORDERS" << endl;

    // Orders* vorder1 = new OrdersDeploy(p1, p1->ownedTerritories[0], 3);
    // Orders* vorder2 = new OrdersAdvance(p1, p1->ownedTerritories[0], p1->ownedTerritories[1], 1);
    // Orders* vorder3 = new OrdersBomb(p1, p2->ownedTerritories[0]);
    // Orders* vorder4 = new OrdersBlockade(p1, p1->ownedTerritories[1]);
    // Orders* vorder5 = new OrdersAirlift(p1, p1->ownedTerritories[0], p1->ownedTerritories[1], 2);
    // Orders* vorder6 = new OrdersNegotiate(p1, p2);

    // Orders* vlist[6] = {vorder1, vorder2, vorder3, vorder4, vorder5, vorder6};

    // cout << "\nVALID ORDERS MEMORY ADDRESSES" << endl;
    // for (int n = 0; n < sizeof(vlist) / sizeof(vlist[0]); n++){
    //     cout << vlist[n] << endl;
    // }

    // cout << "\nVALID ORDERS PRINT AND VALIDITY\n" << endl;
    // for (int n = 0; n < sizeof(vlist) / sizeof(vlist[0]); n++){
    //     cout << *vlist[n] << "IS VALID?: ";
    //     vlist[n]->validate();
    //     cout << endl;
    // }
    // cout << endl;

    // cout << "INVALID ORDERS" << endl;
    // Orders* iorder1 = new OrdersDeploy(p2, p1->ownedTerritories[0], 3);
    // Orders* iorder2 = new OrdersAdvance(p2, p1->ownedTerritories[1], p2->ownedTerritories[0], 10);
    // Orders* iorder3 = new OrdersBomb(p2, p2->ownedTerritories[0]);
    // Orders* iorder4 = new OrdersBlockade(p2, p1->ownedTerritories[1]);
    // Orders* iorder5 = new OrdersAirlift(p2, p1->ownedTerritories[0], p2->ownedTerritories[0], 10);
    // Orders* iorder6 = new OrdersNegotiate(p2, p2);

    // Orders* ilist[6] = {iorder1, iorder2, iorder3, iorder4, iorder5, iorder6};

    // cout << "\nINVALID ORDERS MEMORY ADDRESSES" << endl;
    // for (int n = 0; n < sizeof(ilist) / sizeof(ilist[0]); n++){
    //     cout << ilist[n] << endl;
    // }

    // cout << "\nINVALID ORDERS PRINT AND VALIDITY\n" << endl;
    // for (int n = 0; n < sizeof(ilist) / sizeof(ilist[0]); n++){
    //     cout << *ilist[n] << "IS VALID?: ";
    //     ilist[n]->validate();
    //     cout << endl;
    // }
    // cout << endl;

    // Orders* o1 = new Orders();
    // Orders* o2 = new Orders(*o1);
    // Orders* o3 = new Orders();
    // *o3 = *o1;



    // Player* p1 = new Player(1);
    // p1->ownedTerritories.push_back(new Territory("Montreal", 5, p1));
    // p1->ownedTerritories.push_back(new Territory("Toronto", 4, p1));

    // Player* p2 = new Player(2);
    // p2->ownedTerritories.push_back(new Territory("Miami", 6, p2));
    // p2->ownedTerritories.push_back(new Territory("Talahasee", 2, p2));

    // cout << "VALID ORDERS" << endl;

    // Orders* o1 = new OrdersDeploy(p1, p1->ownedTerritories[0], 3);
    // Orders* o2 = new OrdersAdvance(p1, p1->ownedTerritories[0], p1->ownedTerritories[1], 1);
    // Orders* o3 = new OrdersBomb(p1, p2->ownedTerritories[0]);
    // Orders* o4 = new OrdersBlockade(p1, p1->ownedTerritories[1]);
    // Orders* o5 = new OrdersAirlift(p1, p1->ownedTerritories[0], p1->ownedTerritories[1], 2);
    // Orders* o6 = new OrdersNegotiate(p1, p2);

    // OrdersList* olist = new OrdersList();

    // olist->add(o1);
    // olist->add(o2);
    // olist->add(o3);
    // olist->add(o4);
    // olist->add(o5);
    // olist->add(o6);

    // cout << "\nLIST ADDRESSES LIST 1" << endl;
    // for (auto it : olist->getList())
    //     cout << it << endl;
    
    // cout << "\nLIST DATA LIST 1" << endl;
    // for (auto it : olist->getList())
    //     cout << *it << endl;

    // cout << endl;
    // OrdersList* olist2 = new OrdersList(*olist);

    // cout << "\nLIST ADDRESSES LIST 2" << endl;
    // for (auto it : olist2->getList())
    //     cout << it << endl;
    
    // cout << "\nLIST DATA LIST 2" << endl;
    // for (auto it : olist2->getList())
    //     cout << *it << endl;

    // cout << "ADDRESSES" << endl;
    // cout << o1 << endl;
    // cout << o2 << endl;
    // cout << o3 << endl;

    // cout << "\nDATA" << endl;
    // cout << *o1 << endl;
    // cout << *o2 << endl;
    // cout << *o3 << endl;
    
    Player* p1 = new Player(1);
    Player* p2 = new Player(2);
    Territory* t1 = new Territory("Canada", 3, p1);
    Orders* o1 = new Orders(p1, t1);

    cout << "\nPlayer: " << p1 << " DATA: " << *p1 << endl;
    cout << "\nTerritory: " << t1 << " DATA: " << *t1 << endl;
    cout << "\nOrders: " << o1 << " DATA: " << *o1 << "\n" << endl;

    delete o1;

    cout << "\nPlayer: " << p1 << " DATA: " << *p1 << endl;
    cout << "\nTerritory: " << t1 << " DATA: " << *t1 << endl;
    //cout << "\nOrders: " << o1 << " DATA: " << *o1 << endl;



    return 0;
}