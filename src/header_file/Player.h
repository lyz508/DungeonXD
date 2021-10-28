#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <string>
#include <vector>
#include "GameCharacter.h"
#include "Room.h"
#include "Item.h"
#include "Monster.h"

using namespace std;

#define LIMIT_OF_EQUIP 5

class Item;

class Player: public GameCharacter
{
private:
    Room* currentRoom;
    Room* previousRoom;
    vector<Item> inventory;
    vector<Item> equipment;

    /*Set for judge the difficulty of dungeon*/
    // 0->easy, 1->common, 2->difficult, 3->very hard
    int difficulty;

    // Set for rebuild the player's information
    int currentRoomIndex;
    int previousRoomIndex;

    /*Skill*/
    //0: fire ball, 1: double double!, 2: dead devide
    int skill;
    int skillCoolDown;

    /*Coin*/
    int coin;


public:
    Player();
    Player(string name,int,int,int);
    void addItem(Item);
    void increaseStates(int,int,int);
    void changeRoom(Room*);

    /*Use the skill depends on the skill number*/
    bool useSkill(Object*);

    /*Handle the Equipment*/
    bool handleEquipment();

    /* Virtual function that you need to complete   */
    /* In Player, this function should show the     */
    /* status of player.                            */
    bool triggerEvent(Object* character) override;
    string getInformation();

    /* Set & Get function*/
    void setCurrentRoom(Room*);
    void setPreviousRoom(Room*);
    void setInventory(vector<Item>);
    void setSkill(int);
    void setSkillCoolDown(int);
    void setDifficulty(int);
    void setEquipment(vector<Item>);
    void setCoin(int);
    int getCoin();
    Room* getCurrentRoom() const;
    Room* getPreviousRoom() const;
    vector<Item> getInventory() const;
    int getSkill() const;
    int getSkillCoolDown() const;
    int getDifficulty() const;
    vector<Item> getEquipment() const;

    /*For the controller to change the value outside*/
    vector<Item>* getEquipmentAddress();
    vector<Item>* getInventoryAddress();

    // Need to use the function to reset the position of the player
    void setCurrentRoomIndex(int);
    void setPreviousRoomIndex(int);
    int getCurrentRoomIndex();
    int getPreviousRoomIndex();
};

#endif // PLAYER_H
