#ifndef RECORD_H
#define RECORD_H


#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include "Item.h"
#include "Monster.h"
#include "NPC.h"
#include "Player.h"
#include "Functions.h"
#include "Chest.h"
#include "Exceptions.h"

using namespace std;

/* This is the record system. Get the information of the  */
/* player and rooms then save them to (a) file(s). Notice */
/* that using pass by reference can prevent sending the   */
/* whole vector to the function.                          */



class Record
{
private:
    void savePlayer(Player*, ofstream&);
    void saveRooms(vector<Room>&, ofstream&);
    void saveWholeMonsters(vector<Monster>&, ofstream&);
    void saveWholeNPC(vector<NPC>&, ofstream&);
    void saveWholeChest(vector<Chest>&, ofstream&);

    void loadPlayer(Player*, ifstream&);
    //void loadRooms(vector<Room>&, ifstream&);
    void loadWholeMonster(vector<Monster>&, ifstream&);
    void loadWholeNPC(vector<NPC>&, ifstream&);
    void loadWholeChest(vector<Chest>&, ifstream&);

public:
    Record();
    void saveToFile(Player*, vector<Room>&, vector<NPC>&, vector<Monster>&, vector<Chest>&);
    void loadFromFile(Player*, vector<Room>&, vector<NPC>&, vector<Monster>&, vector<Chest>&)
        throw(CantFindTheLoadFile);

    // for test
    void loadRooms(vector<Room>&, ifstream&);

};

#endif // RECORD_H
