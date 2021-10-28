#ifndef ITEM_H
#define ITEM_H

#include <iostream>
#include <string>
#include <vector>
#include "Object.h"
#include "Player.h"
#include "Functions.h"
using namespace std;

class Player;

class Item: public Object
{
private:
    int hp,atk,def;
    int rare;
    string intro;
public:
    Item();
    Item(string, int, int, int);
    // For load, forbidden the recalculate
    Item(string, int, int, int, int);

    /* Virtual function that you need to complete    */
    /* In Item, this function should deal with the   */
    /* pick up action. You should add status to the  */
    /* player.                                       */
    bool triggerEvent(Object* character) override;

    void reCalculateAttr();

    string shortIntro();

    /* Set & Get function*/
    int getHp() const;
    int getAtk() const;
    int getDef() const;
    int getRare() const;
    string getIntro();
    string getRareS() const;
    void setHp(int);
    void setAtk(int);
    void setDef(int);
    void setRare(int);
    void setIntro(string);
    string getInformation();

    friend ostream& operator << (ostream& out, Item& item);
};

#endif // ITEM_H
