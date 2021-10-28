#include "Monster.h"

Monster::Monster(): GameCharacter("Monster", "default_monster", 1, 1, 1){}

Monster::Monster(string name, int atk, int def, int hp): GameCharacter("Monster", name, atk, def, hp){

}

bool Monster::triggerEvent(Object* player){

    if (player->getTag() != "Player"){
        return false;
    }

    Player* combat_player = dynamic_cast<Player*> (player);
    int brace_len = 21+this->getName().size();

    cout << endl;
    for(int i=0; i<brace_len; i++){
        cout << "=";
    }
    cout << "\n";
    cout << "!!!!" + this->getName() + " has occuered!!!!\n";
    for(int i=0; i<brace_len; i++){
        cout << "=";
    }


    int round = 1, act = 0;
    while(1){
        cout << (*this);
        cout << "What action are you want to do?" << endl
             << "(1) Fight!" << endl
             << "(2) Use The Skill" <<endl
             << "(3) Flee~~~" <<endl
             << "(4) Show self status" << endl;

        int act;
        string input;
        while(1){
            cin >> input;
            if (atoi(input.c_str()) != 0 && atoi(input.c_str()) <= 4){
                break;
            }
            else{
                cout << "Wrong input ! " <<endl;
            }
        }
        act =  atoi(input.c_str());
        int a = this->getAtk() - combat_player->getDef(), b = combat_player->getAtk() - this->getDef();
        switch(act){
        case 1:
            if (a < 0){
                a = 1;
            }
            if (b < 0){
                b = 1;
            }

            cout << endl;
            cout << "______________________________" << endl;
            cout << this->getName() << " gained " << b
                 << " points damage from " << combat_player->getName() << endl;
            this->takeDamage(b);
            cout << combat_player->getName() << " gained " << a
                 << " points damage from " << this->getName() << endl;
            combat_player->takeDamage(a);
            cout << "You now have " << combat_player->getCurHp() << '/' << combat_player->getMaxHp() << endl;
            cout << "==============================" << endl;

            if (combat_player->getSkillCoolDown() > 0){
                combat_player->setSkillCoolDown(combat_player->getSkillCoolDown() - 1);
            }

            break;

        case 2:
            combat_player->useSkill(this);
            break;

        case 3:
            cout << "You RETREAT to the previous room" << endl;
            combat_player->changeRoom(combat_player->getPreviousRoom());
            cout << " (You are now in Room " << combat_player->getCurrentRoom()->getIndex() <<")" << endl;
            break;

        case 4:
            combat_player->triggerEvent(combat_player);
            break;

        default:
            cout << "Please enter again!" << endl;
            break;
        }


        if (combat_player->checkIsDead()){
            cout << "You died LOL!" << endl;
            return true;
        }
        else if(this->checkIsDead()){
            cout << "You Win~" << endl
                 << "You beat the " << this->getName() << "\n\n\n" << endl;
            return true;
        }
    }
}
