#ifndef GAMECHARATER_H
#define GAMECHARATER_H

#include <iostream>
#include <string>
#include "Object.h"
using namespace std;

class GameCharacter: public Object
{
private:
    string name;
    int maxHp;
    int curHp;
    int atk;
    int def;
public:
    GameCharacter();
    GameCharacter(string tag,string name,int,int,int);
    bool checkIsDead();
    int takeDamage(int);

    // let the GameCharacter to become an abstract type
    bool triggerEvent(Object*) = 0;

    /* Set & Get function*/
    void setMaxHp(int);
    void setCurHp(int);
    void setAtk(int);
    void setDef(int);
    int getMaxHp() const;
    int getCurHp() const;
    int getAtk() const;
    int getDef() const;

    virtual string getInformation();

    // friend function
    friend ostream& operator << (ostream& out, const GameCharacter& ca);
};

#endif // GAMECHARATER_H
