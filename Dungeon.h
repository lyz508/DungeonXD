#ifndef DUNGEON_H
#define DUNGEON_H

#include <iostream>
#include <string>
#include <vector>
#include <exception>
#include <random>
#include <time.h>
#include <vector>
#include "Player.h"
#include "Monster.h"
#include "NPC.h"
#include "Room.h"
#include "Record.h"
#include "Chest.h"
#include "Functions.h"

using namespace std;

#define LEN_OF_MAINTAIN 500

class Dungeon{
private:
    vector<Room> rooms;
    vector<Monster> whole_monster;
    vector<NPC> whole_NPC;
    vector<Chest> whole_chest;

    // for maintain the rooms
    int rooms_up[LEN_OF_MAINTAIN];
    int rooms_right[LEN_OF_MAINTAIN];
    int rooms_down[LEN_OF_MAINTAIN];
    int rooms_left[LEN_OF_MAINTAIN];

public:
    Dungeon();
    /*For the load game*/
    void loadGame();

    /* Create a new player, and give him/her basic status */
    void createPlayer();
    void createPlayer(string, int);

    /* Create a map, which include several different rooms */
    bool createMap();

    /* Deal with player's moving action */
    void handleMovement();

    /* Deal with player's interaction with objects in that room */
    void handleEvent(Object*);

    /* Deal with all game initial setting       */
    /* Including create player, create map etc  */
    void startGame();

    /* Deal with the player's action     */
    /* including showing the action list */
    /* that player can do at that room   */
    /* and dealing with player's input   */
    void chooseAction(vector<Object*>);

    /* Check whether the game should end or not */
    /* Including player victory, or he/she dead */
    bool checkGameLogic();

    /* Deal with the whole game process */
    void runDungeon();

    /*Maintain the rooms in case the break on the order*/
    void maintainRooms();

    /*Getter & Setter*/
    int getRoomLength();
    vector<Room*> getRoomAddresses();
    vector<Room>* getRoomPointer();
    /*For GUI controller Save*/
    vector<Room> getWholeRoom();
    vector<Monster> getWholeMonster();
    vector<NPC> getWholeNPC();
    vector<Chest> getWholeChest();
    /*For GUI controller Load*/
    vector<Room>* getWholeRoomAddress();
    vector<Monster>* getWholeMonsterAddress();
    vector<NPC>* getWholeNPCAddress();
    vector<Chest>* getWholeChestAddress();
    void loadGameGUI();



    // for test
    Player player;
};


#endif // DUNGEON_H
