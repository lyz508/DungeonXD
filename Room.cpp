#include "Room.h"

Room::Room(){

}

Room::Room(bool isExit, int index, vector<Object*> objects){
    this->isExit = isExit;
    this->index = index;
    this->objects = objects;
    this->upRoom = nullptr;
    this->downRoom = nullptr;
    this->rightRoom = nullptr;
    this->leftRoom = nullptr;

    // random the num of the monster, npc in the room
    // help the rebuild
    this->monsterNum = rand()%3 + 1;
    this->npcNum = rand()%2 + 1;
    this->chestNum = rand()%2;
}

bool Room::popObject(Object* want_pop){
    if (want_pop){
        for(int i=0; i<this->objects.size(); i++){
            if(this->objects[i] == want_pop){
                this->objects.erase(objects.begin() + i);
                return true;
            }
        }
    }
    return false;
}

void Room::popObject(int index){
    this->objects.erase(objects.begin() + index);
}


/*setter*/
void Room::setUpRoom(Room* room){
    this->upRoom = room;
}

void Room::setDownRoom(Room* room){
    this->downRoom = room;
}

void Room::setRightRoom(Room* room){
    this->rightRoom = room;
}

void Room::setLeftRoom(Room* room){
    this->leftRoom = room;
}

void Room::setIsExit(bool isExit){
    this->isExit = isExit;
}

void Room::setIndex(int index){
    this->index = index;
}

void Room::setObjects(vector<Object*> objects){
    this->objects = objects;
}

// Help the rebuild of the room
void Room::setNpcNum(int num){
    this->npcNum = num;
}

void Room::setMonsterNum(int num){
    this->monsterNum = num;
}

void Room::setChestNum(int num){
    this->chestNum = num;
}


/*getter*/
int Room::getIndex(){
    return this->index;
}

bool Room::getIsExit(){
    return this->isExit;
}

vector<Object*> Room::getObjects(){
    return this->objects;
}

Room* Room::getUpRoom(){
    return this->upRoom;
}

Room* Room::getDownRoom(){
    return this->downRoom;
}

Room* Room::getRightRoom(){
    return this->rightRoom;
}

Room* Room::getLeftRoom(){
    return this->leftRoom;
}

// Help the rebuild of the room
int Room::getNpcNum(){
    return this->npcNum;
}

int Room::getMonsterNum(){
    return this->monsterNum;
}

int Room::getChestNum(){
    return this->chestNum;
}


void Room::push_object(Object* in_object){
    this->objects.push_back(in_object);
}
