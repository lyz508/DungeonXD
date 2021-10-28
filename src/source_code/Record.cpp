#include "Record.h"


Record::Record(){

}


/*Save*/

// Save the player:
//      Including the save of name, atk, def, hp, room, inventory
void Record::savePlayer(Player* player, ofstream& out){
    out << player->getName() << endl
        << player->getAtk() << ' '
        << player->getDef() << ' '
        << player->getCurHp() << ' '
        << player->getMaxHp() << ' '
        << player->getDifficulty() << ' '
        << player->getCoin() << ' '
        << player->getSkill() << ' ' << player->getSkillCoolDown() << ' '
        << player->getCurrentRoom()->getIndex() << ' '
        << player->getPreviousRoom()->getIndex() << ' '
        << player->getEquipment().size() << endl;
    if (player->getEquipment().size() != 0){
        vector<Item> equip = player->getEquipment();
        for(int i=0; i<equip.size(); i++){
            out << equip[i].getName() << endl << equip[i].getAtk() << ' '
                << equip[i].getDef() << ' ' << equip[i].getHp() << ' ' << equip[i].getRare() << endl;
        }
    }

    if (player->getInventory().size() != 0){
        vector<Item> inven = player->getInventory();
        for(int i=0; i<inven.size(); i++){
            out << inven[i].getName() << endl << inven[i].getAtk() << ' '
                << inven[i].getDef() << ' ' << inven[i].getHp() << ' ' << inven[i].getRare() << endl;
        }
    }
}


// Save the whole monster-> to help the rebuild of the dungeon
void Record::saveWholeMonsters(vector<Monster>& whole_monster, ofstream& out){
    for(int i=0; i<whole_monster.size(); i++){
        out << whole_monster[i].getName() << endl
            << whole_monster[i].getAtk() << ' '
            << whole_monster[i].getDef() << ' '
            << whole_monster[i].getCurHp() << ' '
            << whole_monster[i].getMaxHp() << endl;
    }
}


// Save the whole NPC-> to help the rebuild of the dungeon
void Record::saveWholeNPC(vector<NPC>& whole_NPC, ofstream& out){
    for(int i=0; i<whole_NPC.size(); i++){
        out << "*" << endl; // To seperate the NPCs
        out << whole_NPC[i].getName() << endl
            << whole_NPC[i].getAtk() << ' '
            << whole_NPC[i].getDef() << ' '
            << whole_NPC[i].getCurHp() << ' '
            << whole_NPC[i].getMaxHp() << endl;
        vector<Item> commodity = whole_NPC[i].getCommodity();
        for(int ic=0; ic<commodity.size(); ic++){
        out << commodity[ic].getName() << endl << commodity[ic].getAtk() << ' '
            << commodity[ic].getDef() << ' ' << commodity[ic].getHp() << ' ' << commodity[ic].getRare() << endl;
        }
    }
    out << "*"; // To seperate the NPCs
}


// Save the rooms of the dungeon
//      including the num_monster, num_npcs, index, and its neighbers
//  the order: index, up, right, down, left, monsterNum, npcNum, isExit
void Record::saveRooms(vector<Room>& rooms, ofstream& out){

    for (int i_room=0; i_room<rooms.size(); i_room++){
        out << rooms[i_room].getIndex() << '\t';

        if (rooms[i_room].getUpRoom() != nullptr){
            out << rooms[i_room].getUpRoom()->getIndex() << '\t';
        }
        else{
            out << -1 << '\t';
        }
        if (rooms[i_room].getRightRoom() != nullptr){
            out << rooms[i_room].getRightRoom()->getIndex() << '\t';
        }
        else{
            out << -1 << '\t';
        }
        if (rooms[i_room].getDownRoom() != nullptr){
            out << rooms[i_room].getDownRoom()->getIndex() << '\t';
        }
        else{
            out << -1 << '\t';
        }
        if (rooms[i_room].getLeftRoom() != nullptr){
            out << rooms[i_room].getLeftRoom()->getIndex() << '\t';
        }
        else{
            out << -1 << '\t';
        }
        out << rooms[i_room].getMonsterNum() << '\t'
            << rooms[i_room].getNpcNum() << '\t'
            << rooms[i_room].getChestNum() << '\t'
            << rooms[i_room].getIsExit() << endl;
    }
}

void Record::saveWholeChest(vector<Chest>& whole_chest, ofstream& out){
    for(int i=0; i<whole_chest.size(); i++){
        out << "*" << endl; // To seperate the Chests
        out << whole_chest[i].getName() << endl;
        // let the file record if the chest has been opened?
        out << whole_chest[i].getIsOpen() << endl;

        vector<Item> chest = whole_chest[i].getChest();
        for(int ic=0; ic<chest.size(); ic++){
        out << chest[ic].getName() << endl << chest[ic].getAtk() << ' '
            << chest[ic].getDef() << ' ' << chest[ic].getHp() << ' ' << chest[ic].getRare() << endl;
        }
    }
    out << "*";
}






void Record::loadPlayer(Player* player, ifstream& in){
    string eat_player, eat_inventory, name;
    int atk, def, cur_hp, max_hp, item_hp, where_is_player, where_was_player, skill, skillcooldown, difficulty, coin;
    int intEquipNum, rare;
    Item to_push_item;
    vector<Item> to_player_item, to_player_equip;

    getline(in, eat_player);
    name = eat_player; // Name wan't only space
    getline(in, eat_player);
    stringstream ssplayer(eat_player);

    ssplayer >> atk
             >> def
             >> cur_hp
             >> max_hp
             >> difficulty
             >> coin
             >> skill >> skillcooldown
             >> where_is_player >> where_was_player
             >> intEquipNum;

    player->setName(name);
    player->setAtk(atk);
    player->setDef(def);
    player->setCurHp(cur_hp);
    player->setMaxHp(max_hp);
    player->setDifficulty(difficulty);
    player->setSkill(skill);
    player->setCoin(coin);
    player->setSkillCoolDown(skillcooldown);
    player->setCurrentRoomIndex(where_is_player);
    player->setPreviousRoomIndex(where_was_player);

    while(getline(in, eat_inventory)){
        name = eat_inventory;

        getline(in, eat_inventory);
        stringstream ssitem(eat_inventory);

        ssitem >> atk >>def >>item_hp >> rare;
        to_push_item = Item(name, atk, def, item_hp, rare);
        if (intEquipNum > 0){
            to_player_equip.push_back(to_push_item);
            intEquipNum -= 1;
        }
        else{
            to_player_item.push_back(to_push_item);
        }
    }

    player->setInventory(to_player_item);
    player->setEquipment(to_player_equip);
}



void Record::loadWholeMonster(vector<Monster>& whole_monster, ifstream& in){
    string name, eat_monster;
    int atk, def, curHp, maxHp;
    Monster monster;
    while(getline(in, eat_monster)){
        name = eat_monster;

        getline(in, eat_monster);
        stringstream ssmonster(eat_monster);

        ssmonster >> atk >>def >> curHp >> maxHp;
        monster = Monster(name, atk, def, maxHp);
        monster.setCurHp(curHp);

        whole_monster.push_back(monster);
    }
}


void Record::loadWholeNPC(vector<NPC>& whole_npc, ifstream& in){
    // take the list of npcs
    vector<string> seperated_NPC = npc_seperator(in);
    /*
    for(int i=0; i<seperated_NPC.size(); i++){
        cout << "*****" <<endl;
        cout << seperated_NPC[i] << endl;
        cout << "*****" << endl;
    }*/


    NPC npc;
    Item to_push_item;
    string name, item_name, tmp_input;
    int atk, def, curHp, maxHp, rare;
    int item_atk, item_def, item_hp;

    for(int i=0; i<seperated_NPC.size(); i++){
        /* Complete a npc and push into the whole_npc*/
        vector<Item> npc_bag;
        stringstream ssseperated(seperated_NPC[i]);
        // get the name of npc
        getline(ssseperated, name);

        getline(ssseperated, tmp_input);
        stringstream ssattr(tmp_input);
        ssattr >> atk >>def >> curHp >> maxHp;

        while(getline(ssseperated, tmp_input)){
            item_name = tmp_input;
            getline(ssseperated, tmp_input);
            stringstream ssItemAttr(tmp_input);
            ssItemAttr >> item_atk >> item_def >> item_hp >> rare;
            to_push_item = Item(item_name, item_atk, item_def, item_hp, rare);
            npc_bag.push_back(to_push_item);
        }

        npc = NPC(name, base_search("NPC_script"), npc_bag);
        whole_npc.push_back(npc);
    }
}


void Record::loadWholeChest(vector<Chest>& whole_chest, ifstream& in){
    vector<string> seperated_chest = npc_seperator(in);
    Chest chest;
    Item to_push_item;
    string item_name, tmp_input, name;
    int item_atk, item_def, item_hp, item_rare;
    bool isOpen = false;

    for(int i=0; i<seperated_chest.size(); i++){
        /* Complete a npc and push into the whole_npc*/
        vector<Item> chest_bag;
        stringstream ssseperated(seperated_chest[i]);
        // get the name of name
        getline(ssseperated, name);
        //cout << name <<endl;
        getline(ssseperated, tmp_input);
        stringstream sstmp(tmp_input);
        sstmp >> isOpen;

        while(getline(ssseperated, tmp_input)){
            item_name = tmp_input;
            getline(ssseperated, tmp_input);
            stringstream ssItemAttr(tmp_input);
            ssItemAttr >> item_atk >> item_def >> item_hp >> item_rare;
            to_push_item = Item(item_name, item_atk, item_def, item_hp, item_rare);
            chest_bag.push_back(to_push_item);
        }

        chest = Chest(chest_bag);
        chest.setIsOpen(isOpen);
        whole_chest.push_back(chest);
    }
}

// load the rooms
// Careful! only load the index, nums, and the neighber
// Still need to do the objects regeneration in the dungeon
//  Mind the room0 will also have monster, npc num -> rebuil should start from 1
void Record::loadRooms(vector<Room>& rooms, ifstream& in){
    string a_room;
    vector<string> eat_rooms;
    int index, up, right, down, left, monsterNum, npcNum, isExit, chestNum;
    Room to_push_room;

    // To get how many rooms in the list
    while(getline(in, a_room)){
        eat_rooms.push_back(a_room);
    }

    for(int i=0 ;i<eat_rooms.size(); i++){
        rooms.push_back(to_push_room);
    }

    for(int i=0; i<eat_rooms.size(); i++){
        stringstream sseat_rooms(eat_rooms[i]);
        sseat_rooms >> index
                    >> up >> right >> down >> left
                    >> monsterNum >> npcNum >> chestNum
                    >> isExit;

        rooms[i].setIndex(index);
        if (up != -1){
            rooms[i].setUpRoom(&(rooms[up]));
        }
        else{
            rooms[i].setUpRoom(nullptr);
        }

        if (right != -1){
            rooms[i].setRightRoom(&(rooms[right]));
        }
        else{
            rooms[i].setRightRoom(nullptr);
        }

        if (down != -1){
            rooms[i].setDownRoom(&(rooms[down]));
        }
        else{
            rooms[i].setDownRoom(nullptr);
        }

        if (left != -1){
            rooms[i].setLeftRoom(&(rooms[left]));
        }
        else{
            rooms[i].setLeftRoom(NULL);
        }

        rooms[i].setMonsterNum(monsterNum);
        rooms[i].setNpcNum(npcNum);
        rooms[i].setChestNum(chestNum);
        rooms[i].setIsExit(isExit);

        /*cout << index << ' ' << up << ' ' << right << ' ' << down << ' ' << left << ' ' << monsterNum << ' ' << npcNum << ' ' << chestNum << ' ' << isExit << endl;*/
    }
}



void Record::saveToFile(Player* player, vector<Room>& rooms, vector<NPC>& whole_NPC, vector<Monster>& whole_monster, vector<Chest>& whole_chest){

    ofstream player_output, monster_output, NPC_output, room_output, chest_output;
    player_output.open("Player_record.txt", ios::out);
    monster_output.open("Monster_record.txt", ios::out);
    NPC_output.open("NPC_record.txt", ios::out);
    room_output.open("Room_record.txt", ios::out);
    chest_output.open("Chest_record.txt", ios::out);

    if(!player_output|| !monster_output|| !NPC_output|| !room_output || !chest_output){
        cout << "Cant Save The Game!" <<endl;
        exit(-1);
    }



    this->savePlayer(player, player_output);
    this->saveWholeMonsters(whole_monster, monster_output);
    this->saveWholeNPC(whole_NPC, NPC_output);
    this->saveRooms(rooms, room_output);
    this->saveWholeChest(whole_chest, chest_output);


    player_output.close();
    monster_output.close();
    NPC_output.close();
    room_output.close();
    chest_output.close();
}


void Record::loadFromFile(Player* player, vector<Room>& rooms, vector<NPC>& whole_NPC, vector<Monster>& whole_monster, vector<Chest>& whole_chest)
    throw (CantFindTheLoadFile){

    ifstream player_input, monster_input, npc_input, room_input, chest_input;
    player_input.open("Player_record.txt", ios::in);
    monster_input.open("Monster_record.txt", ios::in);
    npc_input.open("NPC_record.txt", ios::in);
    room_input.open("Room_record.txt", ios::in);
    chest_input.open("Chest_record.txt", ios::in);

    if(!player_input){
        throw CantFindTheLoadFile("Player Data");
    }
    if(!monster_input){
        throw CantFindTheLoadFile("Monster Data");
    }
    if(!npc_input){
        throw CantFindTheLoadFile("NPC Data");
    }
    if(!room_input){
        throw CantFindTheLoadFile("Room Data");
    }
    if(!chest_input){
        throw CantFindTheLoadFile("Chest Data");
    }


    this->loadPlayer(player, player_input);
    this->loadWholeMonster(whole_monster, monster_input);
    this->loadWholeNPC(whole_NPC, npc_input);
    this->loadRooms(rooms, room_input);
    this->loadWholeChest(whole_chest, chest_input);

    player_input.close();
    monster_input.close();
    npc_input.close();
    room_input.close();
    chest_input.close();
}
