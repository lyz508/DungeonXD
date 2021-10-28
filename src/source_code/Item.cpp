#include "Item.h"

string rareBase[5] = {"Broken", "Common", "Rare", "SuperRare", "ARTIFACT"};
double rareEffect[5] = {0.2, 1.0, 1.2, 1.5, 2.0};

Item::Item(): Object("Item", "Default"){

}

Item::Item(string name, int atk, int def, int hp): Object("item", name){
    this->atk = atk;
    this->def = def;
    this->hp = hp;
    this->rare = rare_generator();
    this->reCalculateAttr();
    this->intro = base_search(rareBase[this->rare]);
}

Item::Item(string name, int atk, int def, int hp, int rare)
    :Object("item", name)
{
    this->atk = atk;
    this->def = def;
    this->hp = hp;
    this->rare = rare;
    this->intro = base_search(rareBase[this->rare]);
}


/*Setter & Getter*/
void Item::setAtk(int atk){
    this->atk = atk;
}

void Item::setDef(int def){
    this->def = def;
}

void Item::setHp(int hp){
    this->hp = hp;
}

void Item::setRare(int rare){
    this->rare = rare;
}

void Item::setIntro(string intro){
    this->intro = intro;
}


int Item::getAtk() const{
    return this->atk;
}

int Item::getDef() const{
    return this->def;
}

int Item::getHp() const{
    return this->hp;
}

int Item::getRare() const{
    return this->rare;
}

string Item::getIntro(){
    this->setIntro(base_search(rareBase[this->getRare()]));
    return this->intro;
}

string Item::getRareS() const{
    return rareBase[this->rare];
}



bool Item::triggerEvent(Object* character){

    int isValid = 0, newAtk = 0, newDef = 0, newMaxHp = 0, newCurHp = 0;
    /*string valid[4] = {"GameCharacter", "NPC", "Monster", "Player"};
    for(int i=0; i<4; i++){
        if (cha->getTag() == valid[i]){
            isValid = 1;
            break;
        }
    }*/

    if (character->getTag() == "Player"){
        isValid = 1;
    }
    else{
        isValid = 0;
    }

    if (isValid == 0){
        return false;
    }
    else{
        Player* change_player;
        change_player = dynamic_cast<Player*> (character);

        if (change_player){
            change_player->addItem(*this);
            return true;
        }
        else{
            return false;
        }
    }
}


/*Set for recalculate the attrs about the item*/
void Item::reCalculateAttr(){
    double influ = rareEffect[this->rare];
    this->atk = (int)(this->atk * influ);
    this->def = (int)(this->def * influ);
    this->hp = (int)(this->hp * influ);
}

string Item::shortIntro(){
    string output, atk = to_string(this->getAtk()), def = to_string(this->getDef()), hp = to_string(this->getHp());
    output = this->getName() + "\t(" + atk + '/' + def + '/' + hp + ", \'" + this->getRareS() + "\')";
    return output;
}

ostream& operator <<(ostream& out, Item& item){
    item.setIntro(base_search(rareBase[item.rare]));
    out << "\n=======" << item.getName() << "=======\n"
        << "Rare: " << rareBase[item.rare] << endl
        << "Tag: " << item.getTag() << "\n\n"
        << "ATK: " << item.atk << '\n'
        << "DEF: " << item.def << '\n'
        << "HP: " << item.hp << '\n'
        << "\nIntroduction:__________" << endl
        << item.intro <<endl;

    for(int i=0; i<14+item.getName().length(); i++){
        out << "=";
    }
    out << endl;
    return out;
}

string Item::getInformation()
{
    string output = "";
    this->setIntro(base_search(rareBase[this->rare]));

    output += "=======" + this->getName() + string("=======\n")
            + "Rare: " + rareBase[this->rare] + "\n"
            + "Tag: " + this->getTag() + "\n\n"
            + "ATK: " + to_string(this->getAtk()) + "\n"
            + "DEF: " + to_string(this->def) + "\n"
            + "HP: " + to_string(this->hp) + "\n"
            + "\nIntroduction:_______\n"
            + this->intro;

    for(int i=0; i<14+this->getName().length(); i++){
        output += "=";
    }

    output += "\n";

    return output;
}
