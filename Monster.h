#ifndef MONSTER_H
#define MONSTER_H

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include "GameCharacter.h"
#include "Player.h"

using namespace std;

class Monster: public GameCharacter
{
private:
public:
    Monster();
    Monster(string,int,int,int);

    /* Virtual function that you need to complete   */
    /* In Monster, this function should deal with   */
    /* the combat system.                           */
    bool triggerEvent(Object*) override;
};

#endif // MONSTER_H
