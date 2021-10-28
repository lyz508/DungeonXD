#include "NPC.h"

NPC::NPC(): GameCharacter("NPC", "Default_NPC", 1, 1, 1){

}

NPC::NPC(string name, string script, vector<Item> commodity): GameCharacter("NPC", name, 500, 500, 500){
    this->script = script;
    this->commodity = commodity;
}

void NPC::listCommodity(){
    for(int i=0; i< this->commodity.size(); i++){
        cout << "(" << i+1 << ") " << this->commodity[i].shortIntro() << '\n';
    }
}


/*setter getter*/

void NPC::setScript(string script){
    this->script = script;
}

void NPC::setCommodity(vector<Item> commodity){
    this->commodity = commodity;
}

string NPC::getScript(){
    return this->script;
}

vector<Item> NPC::getCommodity(){
    return this->commodity;
}


bool NPC::triggerEvent(Object* player){
    if (player->getTag() != "Player"){
        return false;
    }
    srand(time(NULL));

    Player* trans_player = dynamic_cast<Player*> (player);

    cout << "\n\n========================================" << endl;

    cout << this->getScript() <<endl
         << "I am " <<this->getName() << endl
         << "The transaction will cost the Hp, Be careful!" << endl;

    // Set the price for the commodity
    vector<int> price_commodity;
    for(int i=0; i<this->commodity.size(); i++){
        price_commodity.push_back(rand()%10 + 1);
    }

    while(1){
        string input;

        int max_len;

        if (this->commodity.size() >= 1){
            max_len = this->commodity[0].getName().length();
        }
        else{
            max_len = 0;
        }

        for(int i=0; i<this->commodity.size(); i++){
            if (this->commodity[i].getName().length() > max_len){
                max_len = this->commodity[i].getName().length();
            }
        }

        for(int i=0; i<max_len+4; i++){
            cout << "=";
        }
        cout <<endl;

        this->listCommodity();


        for(int i=0; i<max_len+4; i++){
            cout << "=";
        }


        cout << "Enter q to quit" << endl
             << "What detail of item do you want to see? " <<endl;
        cin >> input;
        if (input[0] == 'q' && input.length() == 1){
            return true;
        }
        else{
            stringstream ssInput(input);
            int real_num;
            ssInput >> real_num;
            if (real_num > this->commodity.size() || real_num <= 0){
                cout << this->getName() << " say: \"Please think about it.\"" << endl;
                continue;
            }
            else{
                real_num -= 1;

                cout << this->commodity[real_num]
                     << "This item will cost " << price_commodity[real_num] << " Hp," << endl
                     << "Your Hp is: " << trans_player->getCurHp() << '/' << trans_player->getMaxHp() << endl
                     << "Do you want to buy? (y/n)" <<endl;
                cin >> input;
                if (input[0] == 'y' && input.length() == 1){
                    trans_player->takeDamage(price_commodity[real_num]);
                    this->commodity[real_num].triggerEvent(trans_player);
                    //trans_player->addItem(this->commodity[real_num]);
                    this->commodity.erase(this->commodity.begin() + (int)real_num);
                    price_commodity.erase(price_commodity.begin() + (int)real_num);
                }
                else{
                    continue;
                }
            }
        }

    }

}
