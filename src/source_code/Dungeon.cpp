#include "Dungeon.h"


Dungeon::Dungeon(){
    for(int i=0; i<LEN_OF_MAINTAIN; i++){
        this->rooms_right[i] = 0;
        this->rooms_down[i] = 0;
        this->rooms_left[i] = 0;
        this->rooms_up[i] = 0;
    }
}

void Dungeon::loadGame(){
    Record record;
    try{
        record.loadFromFile(&(this->player), this->rooms, this->whole_NPC, this->whole_monster, this->whole_chest);
    }
    catch(CantFindTheLoadFile a){
        cout << "Cant't Fund the " << a.getType() << " File" <<endl;
        system("pause");
        exit(-1);
    }


    cout << "Success Load the File !" << endl;

    // Need to reattribute the monster and the npc in the room
    for(int i=1; i<this->rooms.size(); i++){
        vector<Object*> need_object;
        if (i == this->rooms.size()-1){
            need_object.push_back(&(this->whole_monster.back()));
        }
        else{
            for(int ir=3*(this->rooms[i].getIndex()-1); ir<3*(this->rooms[i].getIndex()-1)+this->rooms[i].getMonsterNum(); ir++){
                need_object.push_back(&(this->whole_monster[ir]));
            }
            // push npc to the vector to set the objects of the room
            for(int in=2*(this->rooms[i].getIndex()-1); in<2*(this->rooms[i].getIndex()-1)+rooms[i].getNpcNum(); in++){
                need_object.push_back(&(this->whole_NPC[in]));
            }
            for(int ic=2*(this->rooms[i].getIndex()-1); ic<2*(this->rooms[i].getIndex()-1)+rooms[i].getChestNum(); ic++){
                need_object.push_back(&(this->whole_chest[ic]));
            }
        }
        rooms[i].setObjects(need_object);
    }



    // Set the position of the player
    int index = this->player.getCurrentRoomIndex();
    this->player.setCurrentRoom(&(this->rooms[index]));
    index = this->player.getPreviousRoomIndex();
    this->player.setPreviousRoom(&(this->rooms[index]));



    // pop the monster who is dead, and the chest which has been open
    for(int i=0; i<rooms.size(); i++){
        vector<Object*> obj = this->rooms[i].getObjects();
        for(int ir = 0; ir < obj.size(); ir++){
            if (obj[ir]->getTag() == "NPC" || obj[ir]->getTag() == "Monster"){
                GameCharacter* gamer = dynamic_cast<GameCharacter*> (obj[ir]);
                if (gamer->getCurHp() <= 0){
                    rooms[i].popObject(obj[ir]);
                }
            }
            /*else if (obj[ir]->getTag() == "Chest"){
                Chest* chest = dynamic_cast<Chest*> (obj[ir]);
                if (chest->getIsOpen() == true){
                    rooms[i].popObject(obj[ir]);
                }
            }*/
        }
    }

    for(int i=0; i<this->rooms.size(); i++){
        if (this->rooms[i].getUpRoom() != nullptr){
            this->rooms_up[i] = rooms[i].getUpRoom()->getIndex();
        }
        else{
            this->rooms_up[i] = -1;
        }
        if (rooms[i].getDownRoom() != nullptr){
            this->rooms_down[i] = this->rooms[i].getDownRoom()->getIndex();
        }
        else{
            this->rooms_down[i] = -1;
        }
        if (rooms[i].getRightRoom() != nullptr){
            this->rooms_right[i] = rooms[i].getRightRoom()->getIndex();
        }
        else{
            this->rooms_right[i] = -1;
        }
        if (rooms[i].getLeftRoom() != nullptr){
            this->rooms_left[i] = rooms[i].getLeftRoom()->getIndex();
        }
        else{
            this->rooms_left[i] = -1;
        }
    }


    // test the build
    /*for(int i=0; i<rooms.size(); i++){
        cout << "Index " << rooms[i].getIndex() << endl;
        if (rooms[i].getUpRoom() != nullptr){
            cout << "Up " << rooms[i].getUpRoom()->getIndex() << endl;
        }
        if (rooms[i].getDownRoom() != nullptr){
            cout << "Down " << rooms[i].getDownRoom()->getIndex() << endl;
        }
        if (rooms[i].getRightRoom() != nullptr){
            cout << "Right " << rooms[i].getRightRoom()->getIndex() << endl;
        }
        if (rooms[i].getLeftRoom() != nullptr){
            cout << "left " << rooms[i].getLeftRoom()->getIndex() << endl;
        }
        vector<Object*> obj = this->rooms[i].getObjects();
        for(int im=0; im<obj.size(); im++){
            cout << obj[im]->getName() << endl;
        }

        if (rooms[i].getIsExit() == true){
            cout <<"(Is the end)" << endl;
        }
        else{
            cout << "(Not the end)" << endl;
        }

        cout << endl;
    }*/
}

void Dungeon::loadGameGUI()
{
    // Need to reattribute the monster and the npc in the room
    for(int i=1; i<this->rooms.size(); i++){
        vector<Object*> need_object;
        if (i == this->rooms.size()-1){
            need_object.push_back(&(this->whole_monster.back()));
        }
        else{
            for(int ir=3*(this->rooms[i].getIndex()-1); ir<3*(this->rooms[i].getIndex()-1)+this->rooms[i].getMonsterNum(); ir++){
                need_object.push_back(&(this->whole_monster[ir]));
            }
            // push npc to the vector to set the objects of the room
            for(int in=2*(this->rooms[i].getIndex()-1); in<2*(this->rooms[i].getIndex()-1)+rooms[i].getNpcNum(); in++){
                need_object.push_back(&(this->whole_NPC[in]));
            }
            for(int ic=2*(this->rooms[i].getIndex()-1); ic<2*(this->rooms[i].getIndex()-1)+rooms[i].getChestNum(); ic++){
                need_object.push_back(&(this->whole_chest[ic]));
            }
        }
        rooms[i].setObjects(need_object);
    }



    // Set the position of the player
    int index = this->player.getCurrentRoomIndex();
    this->player.setCurrentRoom(&(this->rooms[index]));
    index = this->player.getPreviousRoomIndex();
    this->player.setPreviousRoom(&(this->rooms[index]));



    // pop the monster who is dead, and the chest which has been open
    for(int i=0; i<rooms.size(); i++){
        vector<Object*> obj = this->rooms[i].getObjects();
        for(int ir = 0; ir < obj.size(); ir++){
            if (obj[ir]->getTag() == "NPC" || obj[ir]->getTag() == "Monster"){
                GameCharacter* gamer = dynamic_cast<GameCharacter*> (obj[ir]);
                if (gamer->getCurHp() <= 0){
                    rooms[i].popObject(obj[ir]);
                }
            }
        }
    }

    for(int i=0; i<this->rooms.size(); i++){
        if (this->rooms[i].getUpRoom() != nullptr){
            this->rooms_up[i] = rooms[i].getUpRoom()->getIndex();
        }
        else{
            this->rooms_up[i] = -1;
        }
        if (rooms[i].getDownRoom() != nullptr){
            this->rooms_down[i] = this->rooms[i].getDownRoom()->getIndex();
        }
        else{
            this->rooms_down[i] = -1;
        }
        if (rooms[i].getRightRoom() != nullptr){
            this->rooms_right[i] = rooms[i].getRightRoom()->getIndex();
        }
        else{
            this->rooms_right[i] = -1;
        }
        if (rooms[i].getLeftRoom() != nullptr){
            this->rooms_left[i] = rooms[i].getLeftRoom()->getIndex();
        }
        else{
            this->rooms_left[i] = -1;
        }
    }

}


void Dungeon::createPlayer(){
    string input;
    cout << "Enter your name: ";
    cin >> input;
    if (input == "Thomas"){
        this->player = Player(input, 9999, 9999, 99999);
    }
    else{
        this->player = Player(input, 15, 8, 50);
    }

    cout << "Choose the Difficulty" << endl
         << "(1) Easy" << endl
         << "(2) Common" << endl
         << "(3) Hard" << endl
         << "(4) Very Hard" << endl;

    while(1){
        cin >>input;

        if (atoi(input.c_str())){
            if (stoi(input) < 1 || stoi(input) > 4){
                cout << "Wrong Input" << endl;
                continue;
            }
            this->player.setDifficulty(atoi(input.c_str())-1);
            break;
        }
        else{
            cout << "Wrong Input!" << endl;
        }
    }
}

void Dungeon::createPlayer(string name, int difficulty)
{
    if (name == "Thomas"){
        this->player = Player(name, 9999, 9999, 99999);
    }
    else{
        this->player = Player(name, 15, 8, 50);
    }

    this->player.setDifficulty(difficulty);
}

bool Dungeon::createMap(){

    /*Preset the monster and the npc*/
    // Difficult: 0->8 rooms 1-> 15 rooms 2->30 rooms 3->50 rooms
    // npc -> rooms*10, monster -> rooms*20, chest -> rooms * 5
    int room_num = 0;
    int gameDiff = this->player.getDifficulty();

    switch(gameDiff){
    case 0: // easy
        room_num = 5;
        break;
    case 1: // common
        room_num = 10;
        break;
    case 2: // hard
        room_num = 30;
        break;
    case 3: // very hard
        room_num = 99;
        break;
    default:
        room_num = 10;
        break;
    }



    int whole_npc_num = room_num*10, whole_monster_num = room_num*20, whole_chest_num = room_num*5;
    string monster_name;
    string item_name, npc_name, script;

    int room_effect = 0;
    for(int i=0; i<whole_monster_num; i++){
        monster_name  = rand_name_generator("Monster");
        room_effect = i/3 + 1;
        Monster monster(monster_name, rand()%((room_effect+gameDiff)*5), rand()%((room_effect+gameDiff)*3), rand()%((room_effect+gameDiff)*10)+1);
        this->whole_monster.push_back(monster);

        // Generate the king of the dungeon
        if (i == whole_monster_num-1){
            int attrBase = 66666, devitor;
            switch(gameDiff){
            case 0:
                devitor = 500;
                break;
            case 1:
                devitor = 1000;
                break;
            case 2:
                devitor = 5000;
                break;
            case 3:
                devitor = 10000;
                break;
            default:
                devitor = 1;
                break;
            }

            Monster demon("KING OF DUNGEON", attrBase%(devitor/10), attrBase%(devitor/10), attrBase%devitor);
            this->whole_monster.push_back(demon);
        }
    }
    for (int i=0; i<whole_npc_num; i++){
        Item the_item;
        room_effect = i+1;
        vector<Item> npc_bag;
        for(int ii=0; ii<3; ii++){
            item_name = rand_name_generator("Item");
            the_item = Item(item_name, rand()%(room_effect*5), rand()%(room_effect*3), rand()%(room_effect*10));
            npc_bag.push_back(the_item);
        }
        npc_name = rand_name_generator("NPC");
        script = base_search("NPC_script");
        NPC npc(npc_name, script, npc_bag);
        this->whole_NPC.push_back(npc);
    }
    for(int i=0; i<whole_chest_num; i++){
        Item the_item;
        room_effect = i+1;
        vector<Item> push_in_chest;
        int how_many_in_chest = rand()%15+1;
        for(int ii=0; ii<how_many_in_chest; ii++){
            item_name = rand_name_generator("Item");
            the_item = Item(item_name, rand()%((room_effect+gameDiff)*5), rand()%((room_effect+gameDiff)*3), rand()%((room_effect+gameDiff)*10));
            push_in_chest.push_back(the_item);
        }
        Chest chest(push_in_chest);
        this->whole_chest.push_back(chest);
    }



    /*Create the Room*/
    vector<Object*> obj;
    int total_num = room_num, created = 0, monster_num = 0, npc_num = 0, chest_num = 0;
    Room room(false, 0, obj);
    this->rooms.push_back(room);
    int now_map = 0;
    this->player.setCurrentRoom(&(this->rooms.back()));
    created += 1;

    // total_num -> set the resolution of the create map
    for(int i=0; i<total_num; i++){
        int neighbor = rand()%4 + 1;

        for(int k=0; k<neighbor; k++){

            // base on the created rooms number to initial the index of the room
            Room gen_room(false, created, obj);
            // push monster to the vector to set the objects of the room
            vector<Object*> need_obj;
            need_obj.reserve(200); // give enough space to class (Question!!)


            // judge if is the last room(need to push the king of the dungeon)
            if (i == total_num-1 && k == neighbor-1){
                need_obj.push_back(&(this->whole_monster.back()));
                gen_room.setObjects(need_obj);
                gen_room.setIsExit(true);

                if (this->rooms[now_map].getUpRoom() == nullptr){
                    gen_room.setDownRoom(&(this->rooms[now_map]));
                    this->rooms.push_back(gen_room);
                    this->rooms[now_map].setUpRoom(&(this->rooms.back()));
                }
                else if(this->rooms[now_map].getRightRoom() == nullptr){
                    gen_room.setLeftRoom(&(this->rooms[now_map]));
                    this->rooms.push_back(gen_room);
                    this->rooms[now_map].setRightRoom(&(this->rooms.back()));
                }
                else if(this->rooms[now_map].getDownRoom() == nullptr){
                    gen_room.setUpRoom(&(this->rooms[now_map]));
                    this->rooms.push_back(gen_room);
                    this->rooms[now_map].setDownRoom(&(this->rooms.back()));
                }
                else if(this->rooms[now_map].getLeftRoom() == nullptr){
                    gen_room.setRightRoom(&(this->rooms[now_map]));
                    this->rooms.push_back(gen_room);
                    this->rooms[now_map].setLeftRoom(&(this->rooms.back()));
                }

                /*cout << "The map has been created! " << endl
                     << "There are " << this->rooms.size() << " rooms in the dungeon" << endl
                     << "The KING OF DUNGEON has already seated on the last room!" << endl
                     << "Try to beat it!" << endl;*/
            }
            else{// for the room isn't the last room
                monster_num = gen_room.getMonsterNum();
                for(int ir=3*(created-1); ir<3*(created-1)+monster_num; ir++){
                    need_obj.push_back(&(this->whole_monster[ir]));
                    //cout << "MM: " << ir << endl; // for test
                }
                // push npc to the vector to set the objects of the room
                npc_num = gen_room.getNpcNum();
                for(int in=2*(created-1); in<2*(created-1)+npc_num; in++){
                    need_obj.push_back(&(this->whole_NPC[in]));
                    //cout << "NN: " << in << endl; // for test
                }
                // push chest to the vector to set the objects of the room
                chest_num = gen_room.getChestNum();
                for(int ic=2*(created-1); ic<2*(created-1)+chest_num; ic++){
                    need_obj.push_back(&(this->whole_chest[ic]));
                }


                // for test
                //cout << "Monster Num: " << monster_num << "\nNpc Num: "  << npc_num << endl;

                gen_room.setObjects(need_obj);

                // Rand a direction to create the room
                int pos = rand()%4 + 1;
                switch(pos){
                case 1: // UpRoom
                    if (this->rooms[now_map].getUpRoom() == nullptr){
                        gen_room.setDownRoom(&(this->rooms[now_map]));
                        this->rooms.push_back(gen_room);
                        this->rooms[now_map].setUpRoom(&(this->rooms.back()));
                        created += 1;
                        break;
                    }
                    else{
                        break;
                        k--;
                    }
                case 2: // RightRoom
                    if (this->rooms[now_map].getRightRoom() == nullptr){
                        gen_room.setLeftRoom(&(this->rooms[now_map]));
                        this->rooms.push_back(gen_room);
                        this->rooms[now_map].setRightRoom(&(this->rooms.back()));
                        created += 1;
                        break;
                    }
                    else{
                        break;
                        k--;
                    }
                case 3: // DownRoom
                    if (this->rooms[now_map].getDownRoom() == nullptr){
                        gen_room.setUpRoom(&(this->rooms[now_map]));
                        this->rooms.push_back(gen_room);
                        this->rooms[now_map].setDownRoom(&(this->rooms.back()));
                        created += 1;
                        break;
                    }
                    else{
                        break;
                        k--;
                    }
                case 4: // LeftRoom
                    if (this->rooms[now_map].getLeftRoom() == nullptr){
                        gen_room.setRightRoom(&(this->rooms[now_map]));
                        this->rooms.push_back(gen_room);
                        this->rooms[now_map].setLeftRoom(&(this->rooms.back()));
                        created += 1;
                        break;
                    }
                    else{
                        break;
                        k--;
                    }
                default:
                    cout << "Wrong on the build" << endl;
                    exit(-20);
                    break;
                }
            }
        }
        now_map = this->rooms.back().getIndex();
    }


    /*Fill in the order of the rooms to help the maintain*/
    for(int i=0; i<this->rooms.size(); i++){
        if (this->rooms[i].getUpRoom() != nullptr){
            this->rooms_up[i] = rooms[i].getUpRoom()->getIndex();
        }
        else{
            this->rooms_up[i] = -1;
        }
        if (rooms[i].getDownRoom() != nullptr){
            this->rooms_down[i] = this->rooms[i].getDownRoom()->getIndex();
        }
        else{
            this->rooms_down[i] = -1;
        }
        if (rooms[i].getRightRoom() != nullptr){
            this->rooms_right[i] = rooms[i].getRightRoom()->getIndex();
        }
        else{
            this->rooms_right[i] = -1;
        }
        if (rooms[i].getLeftRoom() != nullptr){
            this->rooms_left[i] = rooms[i].getLeftRoom()->getIndex();
        }
        else{
            this->rooms_left[i] = -1;
        }
    }

    /*Question: */
    /*
    this->rooms.back().setIsExit(true);
    // generate the king of dungeon
    Monster demon("KING OF DUNGEON", 666, 666, 9999);
    this->whole_monster.push_back(demon);
    this->rooms.back().push_object(&(this->whole_monster.back()));
    */


    /*Test if the map was success created*/
    /*for(int i=0; i<rooms.size(); i++){
        cout << "Index " << rooms[i].getIndex() << endl;
        if (rooms[i].getUpRoom() != NULL){
            cout << "Up " << rooms[i].getUpRoom()->getIndex() << endl;
        }
        if (rooms[i].getDownRoom() != NULL){
            cout << "Down " << rooms[i].getDownRoom()->getIndex() << endl;
        }
        if (rooms[i].getRightRoom() != NULL){
            cout << "Right " << rooms[i].getRightRoom()->getIndex() << endl;
        }
        if (rooms[i].getLeftRoom() != NULL){
            cout << "left " << rooms[i].getLeftRoom()->getIndex() << endl;
        }

        cout << endl;
    }*/



    /*Odd Question*/
    /*cout << "The address of them." <<endl;
    cout << now_map << endl
         << &(this->rooms[0]) << endl;

    cout << "The equal function of them, but get different result" <<endl;
    this->rooms.push_back(next_room);
    cout << now_map->getUpRoom() <<endl;
    cout << this->rooms[0].getUpRoom() <<endl;*/

    return true;
}



void Dungeon::handleMovement(){
    cout << "Move: (" << "You are in the room " << this->player.getCurrentRoom()->getIndex() << ")" << endl;

    int cur_room = this->player.getCurrentRoom()->getIndex();

    vector<int> direction;
    string deri[4] = {"Up", "Right", "Down", "Left"};
    if (this->rooms[cur_room].getUpRoom() != nullptr){
        direction.push_back(0);
    }
    if (this->rooms[cur_room].getRightRoom() != nullptr){
        direction.push_back(1);
    }
    if (this->rooms[cur_room].getDownRoom() != nullptr){
        direction.push_back(2);
    }
    if (this->rooms[cur_room].getLeftRoom() != nullptr){
        direction.push_back(3);
    }

    for(int i=0; i<direction.size(); i++){
        cout << i+1 << " Go " << deri[direction[i]] << endl;
    }

    int act;
    while(1){
        cin >> act;
        act -= 1;
        if (act < direction.size() && act >= 0){
            break;
        }
        else if (act == 98){
            // operation for test
            exit(98);
        }
        else{
            cout << "Wrong Input! " << endl;
        }
    }

    int next = direction[act];
    int next_index = 0;

    switch(next){
    case 0: // Go Up
        next_index = this->rooms[cur_room].getUpRoom()->getIndex();
        this->player.changeRoom(&(this->rooms[next_index]));
        break;
    case 1: // Go Right
        next_index = this->rooms[cur_room].getRightRoom()->getIndex();
        this->player.changeRoom(&(this->rooms[next_index]));
        break;
    case 2: // Go Down
        next_index = this->rooms[cur_room].getDownRoom()->getIndex();
        this->player.changeRoom(&(this->rooms[next_index]));
        break;
    case 3: // Go Left
        next_index = this->rooms[cur_room].getLeftRoom()->getIndex();
        this->player.changeRoom(&(this->rooms[next_index]));
        break;
    default:
        cout <<"Fail on the move" <<endl;
        break;
    }

    cout << "Success! You move to the Room " << this->player.getCurrentRoom()->getIndex() << "..." << endl;
}





void Dungeon::handleEvent(Object* input_obj){
    if (input_obj->getTag() == "Monster"){
        Monster *input_monster = dynamic_cast<Monster*> (input_obj);
        input_monster->triggerEvent(&(this->player));
    }
    else if(input_obj->getTag() == "NPC"){
        NPC
        *input_npc = dynamic_cast<NPC*> (input_obj);
        input_npc->triggerEvent(&(this->player));
    }
    else{
        cout << "Unknown Object" << endl;
    }
}






void Dungeon::startGame(){
    cout << "Do you want to load the save file?(y/n)" << endl;
    string input;

    while(1){
        cin >> input;
        if ((input[0] == 'y' || input[0] == 'n') && input.length() == 1){
            break;
        }
        else{
            cout << "Wrong input! Please try again!" <<endl;
        }
    }

    if (input[0] == 'y'){
        this->loadGame();
    }
    else{
        this->createPlayer();
        this->createMap();
        this->player.setCurrentRoom(&(this->rooms[0]));
        this->player.setPreviousRoom(&(this->rooms[0]));
    }
}






void Dungeon::chooseAction(vector<Object*> room_objects){
    cout << "\n\n\n\n\n\n\n\n&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&" << endl;
    cout << "Choose your action: (You are in the Room " << this->player.getCurrentRoom()->getIndex() << ") "<< endl;
    int isMonster = 0, act = 0, obj_size = room_objects.size(), allow_act = 0;
    string input_act;
    for(int i=0; i<obj_size; i++){
        cout << "(" << i+1 << ") ";
        if (room_objects[i]->getTag() == "Monster"){
            cout << "Fight with " << room_objects[i]->getName() << endl;
            isMonster = 1;
        }
        else if (room_objects[i]->getTag() == "NPC"){
            cout << "Talk to " << room_objects[i]->getName() <<endl;
        }
        else if(room_objects[i]->getTag() == "Chest"){
            Chest* cc = dynamic_cast<Chest*> (room_objects[i]);
            cout << "Open the " << room_objects[i]->getName();
            if (cc->getIsOpen() == true){
                cout << " (opened)" <<endl;
            }
            else{
                cout << endl;
            }
        }
    }
    if (isMonster == 0){
        cout << "(" << obj_size+1 << ") Move out of the room" << endl;
        cout << "(" << obj_size+2 <<") Show the status of player" << endl;
        cout << "(" << obj_size+3 << ") Save to file" << endl;
        cout << "(" << obj_size+4 << ") Equip Item" << endl;
        allow_act = 4;
    }
    else{
        cout << "(" << obj_size+1 <<") Show the status of player" << endl;
        cout << "(" << obj_size+2 << ") Save to file" << endl;
        cout << "(" << obj_size+3 << ") Equip Item" << endl;
        allow_act = 3;
    }

    while (1){
        cin >> input_act;

        if (atoi(input_act.c_str()) == 0){
            cout << "Wrong Input" << endl;
            continue;
        }
        else{
            act = atoi(input_act.c_str());
        }

        act -= 1;
        // for test
        if (act == 776){
            exit(7777777);
        }

        if(act >= obj_size+allow_act || act < 0){
            cout << "Wrong input" << endl;
        }
        else{
            break;
        }
    }

    // there are still monster in the room
    if (act == obj_size && isMonster == 1){
        this->player.triggerEvent(&(this->player));
    }
    else if (act == obj_size+1 && isMonster == 1){
        Record record;
        this->maintainRooms();
        record.saveToFile(&(this->player), this->rooms, this->whole_NPC, this->whole_monster, this->whole_chest);
        cout << "Success Save!" << endl;
    }
    else if(act == obj_size+2 && isMonster == 1){
        this->player.handleEquipment();
    }
    // there is no monster in the room
    else if(isMonster == 0 && act == obj_size){
    // Move out of the room
        this->handleMovement();
    }
    else if (isMonster == 0 && act == obj_size+1){
    // Show the status of the player
        this->player.triggerEvent(&(this->player));
    }
    else if(isMonster == 0 && act == obj_size+2){
    // Move out of the room
        Record record;
        this->maintainRooms();
        record.saveToFile(&(this->player), this->rooms, this->whole_NPC, this->whole_monster, this->whole_chest);
        cout << "Success Save!" << endl;
    }
    else if(isMonster == 0 && act == obj_size+3){
        this->player.handleEquipment();
    }
    else if (room_objects[act]->getTag() == "Monster"){ // Fight with monster
        Monster *monster;
        monster = dynamic_cast<Monster*> (room_objects[act]);
        monster->triggerEvent(&(this->player));
        if (monster->checkIsDead() == true){
            this->rooms[this->player.getCurrentRoom()->getIndex()].popObject(room_objects[act]);
        }
    }
    else if(room_objects[act]->getTag() == "NPC"){ // Trade with NPC
        NPC *npc;
        npc = dynamic_cast<NPC*> (room_objects[act]);
        npc->triggerEvent(&(this->player));
    }
    else if(room_objects[act]->getTag() == "Chest"){
        // Open the chest
        if (isMonster == 1){
            cout << "Please Beat all the Monster" << endl
                 << "Then you are able to open the chest" << endl;
        }
        else if(isMonster == 0){
            Chest* chest;
            chest = dynamic_cast<Chest*> (room_objects[act]);
            if (chest->getIsOpen() == true){
                cout << "The chest has been opened" <<endl;
            }
            else{
                chest->triggerEvent(&(this->player));
                chest->setIsOpen(true);
            }
        }
    }
    else{
        cout << "for what? " << endl;
    }


    // test
    /*for(int i=0; i<rooms.size(); i++){
        cout << "Index " << rooms[i].getIndex() << endl;
        if (rooms[i].getUpRoom() != NULL){
            cout << "Up " << rooms[i].getUpRoom()->getIndex() << endl;
        }
        if (rooms[i].getDownRoom() != NULL){
            cout << "Down " << rooms[i].getDownRoom()->getIndex() << endl;
        }
        if (rooms[i].getRightRoom() != NULL){
            cout << "Right " << rooms[i].getRightRoom()->getIndex() << endl;
        }
        if (rooms[i].getLeftRoom() != NULL){
            cout << "left " << rooms[i].getLeftRoom()->getIndex() << endl;
        }
        if (rooms[i].getIsExit() == true){
            cout <<"(Is the end)" << endl;
        }
        else{
            cout << "(Not the end)" << endl;
        }

        cout << endl;
    }*/

    /*for (int i=0; i<30; i++){
        cout << this->rooms_up[i] << ' ' << this->rooms_right[i] << ' ' << this->rooms_down[i] << ' ' << this->rooms_left[i] << endl;
    }*/
}


bool Dungeon::checkGameLogic(){
    if (this->player.checkIsDead() == true){
        //cout << "You are dead! The Game is OVER" << endl;
        return false;
    }
    else if(this->player.getCurrentRoom() == &(this->rooms.back())){
        vector<Object*> check_king;
        check_king = this->player.getCurrentRoom()->getObjects();
        int isKingExist = 0;
        for(int i=0; i<check_king.size(); i++){
            if (check_king[i]->getName() == "KING OF DUNGEON"){
                isKingExist = 1;
            }
        }

        if (isKingExist == 0){
            /*cout << "You successfully beat the 'KING OF DUNGEON'" << endl
                 << "CONGRADULATION!! The game is OVER" << endl;*/
            return false;
        }
        else{
            return true;
        }
    }
    else {
        return true;
    }
}

/*Maintain the order of the rooms, in case the break on the order*/
void Dungeon::maintainRooms(){
    for(int order = 0; order < this->rooms.size(); order++){
        if (this->rooms_up[order] != -1){
            this->rooms[order].setUpRoom(&(this->rooms[this->rooms_up[order]]));
        }
        else{
            this->rooms[order].setUpRoom(nullptr);
        }
        if (this->rooms_right[order] != -1){
            this->rooms[order].setRightRoom(&(this->rooms[this->rooms_right[order]]));
        }
        else{
            this->rooms[order].setRightRoom(nullptr);
        }
        if (this->rooms_down[order] != -1){
            this->rooms[order].setDownRoom(&(this->rooms[this->rooms_down[order]]));
        }
        else{
            this->rooms[order].setDownRoom(nullptr);
        }
        if (this->rooms_left[order] != -1){
            this->rooms[order].setLeftRoom(&(this->rooms[this->rooms_left[order]]));
        }
        else{
            this->rooms[order].setLeftRoom(nullptr);
        }
    }
}

int Dungeon::getRoomLength()
{
    return this->rooms.size();
}

vector<Room *> Dungeon::getRoomAddresses()
{
    vector<Room*> output;

    for (int i=0; i<this->rooms.size(); i++){
        output.push_back(&(this->rooms[i]));
    }

    return output;
}

vector<Room> *Dungeon::getRoomPointer()
{
    return &(this->rooms);
}

vector<Room> Dungeon::getWholeRoom(){
    return this->rooms;
}

vector<NPC> Dungeon::getWholeNPC(){
    return this->whole_NPC;
}

vector<Monster> Dungeon::getWholeMonster()
{
    return this->whole_monster;
}

vector<Chest> Dungeon::getWholeChest(){
    return this->whole_chest;
}

vector<Room> *Dungeon::getWholeRoomAddress()
{
    return &(this->rooms);
}

vector<NPC> *Dungeon::getWholeNPCAddress()
{
    return &(this->whole_NPC);
}

vector<Monster> *Dungeon::getWholeMonsterAddress()
{
    return &(this->whole_monster);
}

vector<Chest> *Dungeon::getWholeChestAddress()
{
    return &(this->whole_chest);
}



void Dungeon::runDungeon(){
    // Create Player and Map, set player to the first room
    this->startGame();
    while(this->checkGameLogic() == true){
        this->chooseAction(this->player.getCurrentRoom()->getObjects());
        this->maintainRooms();
    }
    if (this->player.checkIsDead() == false){
        exit(666666);
    }
    else{
        exit(1);
    }
}


// getter for test
/*vector<Room> Dungeon::getRooms(){
    return this->rooms;
}

Player* Dungeon::getPlayer(){
    return &(this->player);
}*/
