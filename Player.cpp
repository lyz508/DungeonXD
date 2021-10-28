#include "Player.h"

Player::Player(): GameCharacter("Player", "default_player", 1, 1, 1){

}

Player::Player(string name, int atk, int def, int hp): GameCharacter("Player", name, atk, def, hp){
    this->currentRoom = nullptr;
    this->previousRoom = nullptr;
    this->skill = rand()%3;
    this->skillCoolDown = 0;
    this->difficulty = 0;
    this->coin = rand()%10 + 1;
}


/*Set get function*/
void Player::setCurrentRoom(Room* cur_room){
    this->currentRoom = cur_room;
    this->currentRoomIndex = cur_room->getIndex();
}

void Player::setPreviousRoom(Room* pre_room){
    this->previousRoom = pre_room;
}

void Player::setInventory(vector<Item> itemList){
    this->inventory = itemList;
}

void Player::setCurrentRoomIndex(int index){
    this->currentRoomIndex = index;
}

void Player::setPreviousRoomIndex(int index){
    this->previousRoomIndex = index;
}

void Player::setSkill(int skill){
    this->skill = skill;
}

void Player::setSkillCoolDown(int cool){
    this->skillCoolDown = cool;
}

void Player::setDifficulty(int diff){
    if (diff < 0 || diff > 3){
        cout << "Unsure difficult!?" <<endl;
    }
    else{
        this->difficulty = diff;
    }
}

void Player::setEquipment(vector<Item> eq){
    this->equipment = eq;
}

void Player::setCoin(int c)
{
    this->coin = c;
}

int Player::getCoin()
{
    return this->coin;
}


Room* Player::getPreviousRoom() const{
    return this->previousRoom;
}

Room* Player::getCurrentRoom() const{
    return this->currentRoom;
}

vector<Item> Player::getInventory() const{
    return this->inventory;
}

int Player::getSkill() const{
    return this->skill;
}

int Player::getSkillCoolDown() const{
    return this->skillCoolDown;
}

int Player::getDifficulty() const{
    return this->difficulty;
}

vector<Item> Player::getEquipment() const{
    return this->equipment;
}

vector<Item> *Player::getEquipmentAddress()
{
    return &(this->equipment);
}

vector<Item> *Player::getInventoryAddress()
{
    return &(this->inventory);
}

/*Use to rebuild the player's imformation*/
int Player::getCurrentRoomIndex(){
    return this->currentRoomIndex;
}

int Player::getPreviousRoomIndex(){
    return this->previousRoomIndex;
}


bool Player::handleEquipment(){
    this->triggerEvent(this);

    int intBraceLen = 14+this->getName().length(), intWantItem = 0, intOffItem = 0;
    string input;

    for (int i=0; i<intBraceLen; i++){
        cout << "=";
        if (i == intBraceLen-1) {cout << endl;}
    }

    cout << "Choose the Item you want to equip: (q to quit)";
    while (1){
        cin >> input;

        if (input == "q"){
            return false;
        }

        if (atoi(input.c_str())){
            intWantItem = stoi(input);
            if (intWantItem-1 >= this->inventory.size() || intWantItem-1 < 0){
                cout << "Wrong Input!" << endl;
            }
            else{
                intWantItem -= 1;
                break;
            }
        }
        else{
            cout << "Wrong Input!" << endl;
        }
    }


    cout << this->inventory[intWantItem];

    if (this->equipment.size() < LIMIT_OF_EQUIP){
        // for bag haven't been fulled
        this->equipment.push_back(this->inventory[intWantItem]);
        this->increaseStates(this->inventory[intWantItem].getAtk(), this->inventory[intWantItem].getDef(), this->inventory[intWantItem].getHp());
        cout << "The " << this->inventory[intWantItem].getName() <<" has been equip." << endl;
        this->inventory.erase(this->inventory.begin() + intWantItem);
    }
    else{
        cout << "The bag is Full!!" << endl
             << "Choose the Item you want to take off: (q to quit)";

        while (1){
            cin >> input;

            if (input == "q"){
                return false;
            }

            if (atoi(input.c_str())){
                intOffItem = stoi(input);
                if (intOffItem-1 >= this->equipment.size() || intOffItem-1 < 0){
                    cout << "Wrong Input!" << endl;
                }
                else{
                    intOffItem -= 1;
                    break;
                }
            }
            else{
                cout << "Wrong Input!" << endl;
            }
        }

        this->increaseStates(-(this->equipment[intOffItem].getAtk()), -(this->equipment[intOffItem].getDef()), -(this->equipment[intOffItem].getAtk()));
        cout << "The " << this->equipment[intOffItem].getName() << " has been taken off" << endl;
        this->inventory.push_back(this->equipment[intOffItem]);
        this->equipment.erase(this->equipment.begin() + intOffItem);
        this->increaseStates(this->inventory[intWantItem].getAtk(), this->inventory[intWantItem].getDef(), this->inventory[intWantItem].getHp());
        this->equipment.push_back(this->inventory[intWantItem]);
        cout << "The " << this->inventory[intWantItem].getName() <<" has been equip." << endl;
        this->inventory.erase(this->inventory.begin() + intWantItem);
    }

    return true;
}



void Player::addItem(Item item){
    this->inventory.push_back(item);
    //item.triggerEvent();
}

void Player::increaseStates(int atk, int def, int hp){
    this->setAtk(this->getAtk() + atk);
    this->setDef(this->getDef() + def);
    this->setCurHp(this->getCurHp() + hp);
    this->setMaxHp(this->getMaxHp() + hp);
}

void Player::changeRoom(Room* cur_room){
    Room* tmp_room = this->currentRoom;
    this->currentRoom = cur_room;
    this->previousRoom = tmp_room;
}



bool Player::useSkill(Object* target){
    switch(this->skill){

    case(0):{//fire ball
        string input;

        cout << "Want use Fire Ball? ";
        while(1){
            cin >> input;
            if (input.length() == 1 && input[0] == 'y'){
                break;
            }
            else if(input.length() == 1 && input[0] == 'n'){
                return true;
            }
            else{
                cout << "Wrong input!" <<endl;
            }
        }


        if (target->getTag() != "Monster"){
            cout << "Invalid skill target!" <<endl;
            return false;
        }
        else if (this->skillCoolDown > 0){
            cout << "Skill is in the cool down" << endl
                 << "It need " <<this->skillCoolDown << " rounds to recover." <<endl;
            return true;
        }

        int dmg = this->getAtk() * 3;

        Monster* monster = dynamic_cast<Monster*> (target);

        monster->takeDamage(dmg);
        cout << "Used Fire ball!" << endl
             << "The monster has taken " << dmg << " points damage." << endl;

        this->skillCoolDown += 2;

        break;
    }
    case(1):{// double double!
        string input;

        cout << "Want use Double Double? ";
        while(1){
            cin >> input;
            if (input.length() == 1 && input[0] == 'y'){
                break;
            }
            else if(input.length() == 1 && input[0] == 'n'){
                return true;
            }
            else{
                cout << "Wrong input!" <<endl;
            }
        }

        if(target->getTag() != "Monster"){
            cout << "Invalid skill target!" <<endl;
            return false;
        }
        else if (this->skillCoolDown > 0){
            cout << "Skill is in the cool down" << endl
                 << "It need " <<this->skillCoolDown << " rounds to recover." <<endl;
            return true;
        }


        int dmg = this->getAtk() * 2;

        Monster* monster = dynamic_cast<Monster*> (target);

        monster->takeDamage(dmg);
        cout << "Used Double Double!" << endl
             << "The monster has taken " << dmg << " points damage." << endl;
        monster->takeDamage(dmg);
        cout << "Used Double Double!" << endl
             << "The monster has taken " << dmg << " points damage." << endl;

        this->skillCoolDown += 3;

        break;
    }

    case(2):{// dead devide
        string input;

        cout << "Want use Dead Devide? ";
        while(1){
            cin >> input;
            if (input.length() == 1 && input[0] == 'y'){
                break;
            }
            else if(input.length() == 1 && input[0] == 'n'){
                return true;
            }
            else{
                cout << "Wrong input!" <<endl;
            }
        }

        if(target->getTag() != "Monster"){
            cout << "Invalid skill target!" <<endl;
            return false;
        }
        else if (this->skillCoolDown > 0){
            cout << "Skill is in the cool down" << endl
                 << "It need " <<this->skillCoolDown << " rounds to recover." <<endl;
            return true;
        }

        int success = rand()%2;

        Monster* monster = dynamic_cast<Monster*> (target);

        if (success == 1){
            monster->setCurHp(0);
            cout << "Success Use the DEAD DEVIDE!!" <<endl
                 << monster->getName() <<" has dead!" <<endl;
        }
        else{
            cout << "Fail on the DEAD DEVIDE!!" << endl
                 << "Your soul has devoured by the HELL!!" <<endl;
            this->setCurHp(0);
        }

        break;
    }
    default:
        cout << "Ability has Wrong!" << endl;

    }

    return true;
}



/*Show the status of player*/
// overwrite the virtual function
bool Player::triggerEvent(Object* character){
    if (character->getTag() == "Player"){
        Player* player;
        player = dynamic_cast<Player*> (character);

        cout << "\n=======" << player->getName() << "=======\n"
            << "Tag: " << player->getTag() << "\n\n"
            << "ATK: " << player->getAtk() << '\n'
            << "DEF: " << player->getDef() << '\n'
            << "HP: " << player->getCurHp() << '/' << player->getMaxHp() << '\n'
            << "Skill: ";
        switch(this->skill){
        case 0:
            cout << "Fire Ball" << endl;
            break;
        case 1:
            cout << "Double Double" << endl;
            break;
        case 2:
            cout << "Dead Devide" <<endl;
            break;
        default:
            cout << "Wrong on skill output!" <<endl;
            break;
        }

        cout << "Difficulty: ";
        switch(this->difficulty){
        case 0:
            cout << "Easy" << endl;
            break;
        case 1:
            cout << "Common" << endl;
            break;
        case 2:
            cout << "Hard" <<endl;
            break;
        case 3:
            cout << "Very Hard" <<endl;
            break;
        default:
            cout << "Something wrong on the Difficult setting!" << endl
                 << "Please restart the game!!" <<endl;
            break;
        }

        for(int i=0; i<14+player->getName().length(); i++){
            cout << "=";
        }
        cout << endl;
        cout << "Equipment: " << endl;

        if (this->equipment.size() == 0){
            cout << "null QAQ" <<endl;
        }
        else{
            for(int i=0; i<equipment.size(); i++){
                cout << "(" << i+1 << ") " << this->equipment[i].shortIntro() <<endl;
            }

        }

        for(int i=0; i<14+player->getName().length(); i++){
            cout << "=";
        }
        cout << endl;

        cout << "Item: " << endl;
        if (this->inventory.size() == 0){
            cout << "null QAQ" <<endl;
        }
        else{
            for(int i=0; i<inventory.size(); i++){
                cout << "(" << i+1 << ") " << this->inventory[i].shortIntro() <<endl;
            }

        }

        for(int i=0; i<14+player->getName().length(); i++){
            cout << "=";
        }
        cout << endl;

        return true;
    }
    else{
        return false;
    }
}

string Player::getInformation()
{
    string introduction = "";

    introduction +=
         "Name: " + this->getName() + "\n\n"
        + "ATK: " + to_string(this->getAtk()) + "\n"
        + "DEF: " + to_string(this->getDef()) + "\n"
        + "HP: " + to_string(this->getCurHp()) + "/" + to_string(this->getMaxHp()) + "\n"
        + "Coin: " + to_string(this->coin) + "\n"
        + "Skill: ";
    switch(this->skill){
    case 0:
        introduction += "Fire Ball";
        break;
    case 1:
        introduction += "Double Double";
        break;
    case 2:
        introduction += "Dead Devide";
        break;
    default:
        introduction += "Wrong on skill output!\n";
        break;
    }

    introduction += " (cooldown: " + to_string(this->skillCoolDown) + ")\n";

    introduction += "Difficulty: ";
    switch(this->difficulty){
    case 0:
        introduction += "Easy\n";
        break;
    case 1:
        introduction += "Common\n";
        break;
    case 2:
        introduction += "Hard\n";
        break;
    case 3:
        introduction += "Very Hard\n";
        break;
    default:
        break;
    }
    return introduction;
}


