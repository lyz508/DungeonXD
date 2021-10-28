#include "GameCharacter.h"

GameCharacter::GameCharacter(): Object("GameCharacter", "default"){
    this->atk = 1;
    this->def = 1;
    this->maxHp = 1;
    this->curHp = 1;
}

GameCharacter::GameCharacter(string tag, string name, int atk, int def, int hp): Object(tag, name){
    this->atk = atk;
    this->def = def;
    this->maxHp = hp;
    this->curHp = hp;
}

void GameCharacter::setAtk(int atk){
    this->atk = atk;
}

void GameCharacter::setDef(int def){
    this->def = def;
}

void GameCharacter::setMaxHp(int max_hp){
    this->maxHp = max_hp;
}

void GameCharacter::setCurHp(int cur_hp){
    this->curHp = cur_hp;
}

int GameCharacter::getAtk() const{
    return this->atk;
}

int GameCharacter::getDef() const{
    return this->def;
}


int GameCharacter::getCurHp() const{
    return this->curHp;
}

int GameCharacter::getMaxHp() const{
    return this->maxHp;
}

bool GameCharacter::checkIsDead(){
    if (curHp <= 0){
        return true;
    }
    else{
        return false;
    }
}

int GameCharacter::takeDamage(int dmg){
    this->curHp -= dmg;
    return this->curHp;
}

ostream& operator << (ostream& out, const GameCharacter& ca){
    out << "\n=======" << ca.getName() << "=======\n"
         << "Tag: " << ca.getTag() << "\n\n"
         << "ATK: " << ca.getAtk() << '\n'
         << "DEF: " << ca.getDef() << '\n'
         << "HP: " << ca.getCurHp() << '/' << ca.getMaxHp() << '\n';
    for(int i=0; i<14+ca.getName().length(); i++){
        out << "=";
    }
    out << endl;
    return out;
}

string GameCharacter::getInformation()
{
    string output;

    output += "=======";
    output += this->name;
    output += "=======\n"
              "Tag: ";
    output += this->getTag();
    output += "\nATK: ";
    output += to_string(this->getAtk());
    output += "\nDEF: ";
    output += to_string(this->getDef());
    output += "\nHp: ";
    output += to_string(this->getCurHp()) + "/" + to_string(this->getMaxHp()) + "\n";
    for (int i=0; i<14+this->name.length(); i++){
        output += "=";
    }
    output += "\n";

    return output;
}
