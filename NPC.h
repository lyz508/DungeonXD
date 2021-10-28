#ifndef NPC_H
#define NPC_H

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <random>
#include <time.h>
#include "GameCharacter.h"
#include "Player.h"
#include "Item.h"

using namespace std;

class NPC: public GameCharacter
{
private:
    string script;
    vector<Item> commodity;
public:
    NPC();
    NPC(string name, string script, vector<Item>);
    void listCommodity(); /*print all the Item in this NPC*/

    /* Virtual function that you need to complete   */
    /* In NPC, this function should deal with the   */
    /* transaction in easy implementation           */
    bool triggerEvent(Object*);

    /* Set & Get function*/
    void setScript(string);
    void setCommodity(vector<Item>);
    string getScript();
    vector<Item> getCommodity();
};



#endif // NPC_H
