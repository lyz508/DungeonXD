#ifndef ROOM_H
#define ROOM_H

#include <iostream>
#include <string>
#include <vector>
#include "Object.h"

using namespace std;

class Room
{
private:
    Room* upRoom;
    Room* downRoom;
    Room* leftRoom;
    Room* rightRoom;
    bool isExit;
    int index;
    int monsterNum;
    int npcNum;
    int chestNum;
    vector<Object*> objects; /*contain 1 or multiple objects, including monster, npc, etc*/
public:
    Room();
    Room(bool, int, vector<Object*>);
    bool popObject(Object*); /*pop out the specific object, used when the interaction is done*/
    void popObject(int index);

    /* Set & Get function*/
    void setUpRoom(Room*);
    void setDownRoom(Room*);
    void setLeftRoom(Room*);
    void setRightRoom(Room*);
    void setIsExit(bool);
    void setIndex(int);
    void setObjects(vector<Object*>);

    void setMonsterNum(int);
    void setNpcNum(int);
    void setChestNum(int);
    int getMonsterNum();
    int getNpcNum();
    int getChestNum();

    bool getIsExit();
    int getIndex();
    vector<Object*> getObjects();
    Room* getUpRoom();
    Room* getDownRoom();
    Room* getLeftRoom();
    Room* getRightRoom();
    void push_object(Object*);
};

#endif // ROOM_H
