#ifndef CHEST_H
#define CHEST_H

#include <iostream>
#include <vector>
#include "Item.h"
#include "Object.h"
#include "Player.h"
using namespace std;

class Chest: public Object{
public:
    Chest();
    Chest(vector<Item>);

    void setChest(vector<Item>);


    void showItem(int index_1);

    bool triggerEvent(Object*) override;

    bool getIsOpen();
    void setIsOpen(bool);

    vector<Item> getChest();

    friend ostream& operator << (ostream& out, Chest& chest);


private:
    bool isOpen;
    vector<Item> chest;
};



#endif // CHEST_H
