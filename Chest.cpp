#include "Chest.h"

string chest_title[5] = {"Poor", "Normal", "Rare", "Super Rare", "ARTIFACT"};

Chest::Chest(){
}

Chest::Chest(vector<Item> items){
    this->chest = items;
    this->setTag("Chest");

    int index = items.size()/3;
    if (index >= 5){
        index = 4;
    }
    string s_name = chest_title[index] + " Chest";
    this->setName(s_name);
    this->isOpen = false;
}



vector<Item> Chest::getChest() {
    return this->chest;
}

// to check that if the chest has been open -> help the rebuild
bool Chest::getIsOpen(){
    return this->isOpen;
}

void Chest::setChest(vector<Item> items){
    this->chest = items;
}

void Chest::setIsOpen(bool is){
    this->isOpen = is;
}


bool Chest::triggerEvent(Object* player){
    if (player == nullptr){
        return false;
    }
    else{
        Player* real_player = dynamic_cast<Player*> (player);

        int give = this->chest.size();

        for(int i=0; i<give; i++){
            this->chest[i].triggerEvent(real_player);
        }

        this->isOpen = true;
        return true;
    }
}

void Chest::showItem(int index_1){
    cout << this->chest[index_1-1];
}

ostream& operator << (ostream& out, Chest& chest){
    out << "====" << chest.getName() << "====" << endl;
    vector<Item> items = chest.getChest();
    for(int i=0; i<items.size(); i++){
        out << "(" << i+1 << ") " << items[i].getName() << endl;
    }
    for(int i=0; i<8+chest.getName().size(); i++){
        out << "=";
    }
    out << endl;
    return out;
}
