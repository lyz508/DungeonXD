#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , d(nullptr)
{
    ui->setupUi(this);
    ui->txtBrowserPlayerInformation->setAlignment(Qt::AlignHCenter);
    ui->txtBrowserActionMenu->setText("Hello, Welcome to the Dungeon.\n"
                                   "Enter the player name in the \'Create Dungeon\'\n\n"
                                   "Then, Push the \'Create Player\' buttom\n"
                                   "  1. Enter the Name of yout character.\n"
                                   "  2. Enter type : [player_name] [Difi -difficulty]\n"
                                   "  3. The Difficulty is from 1 to 4 (easy ~ very hard)\n"
                                   "  4. For example: John Difi 1\n"
                                   "\n*This action will automatically create the dungeon."
                                   "\n*If you want to load the file, type \'load\' to load the file.");

    this->allowAct = 0;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::renewActionBag()
{
    /*Check if the game id end*/
    if(this->checkGameLogic() == true){
        /*Renew the player Information*/
        string player_information = this->d->player.getInformation();
        ui->txtBrowserPlayerInformation->setText(s2q(player_information));

        string action_output = "", bag_output_i = "", bag_output_e;

        /*Renew bag information*/
        if (this->d->player.getEquipment().size() == 0){
            bag_output_e += "null QAQ\n";
        }
        else{
            for(int i=0; i< this->d->player.getEquipment().size(); i++){
                bag_output_e += "(" + to_string(i+1) + ") " + d->player.getEquipment()[i].shortIntro() + "\n";
            }
        }


        if (this->d->player.getInventory().size() == 0){
            bag_output_i += "null QAQ\n";
        }
        else{
            for(int i=0; i<this->d->player.getInventory().size(); i++){
                bag_output_i += "(" + to_string(i+1) + ") " + this->d->player.getInventory()[i].shortIntro() + "\n";
            }
        }

        ui->txtBrowserPlayerEquipment->setText(s2q(bag_output_e));
        ui->txtBrowserPlayerInventory->setText(s2q(bag_output_i));




        this->d->maintainRooms();
        /*Renew Action Menu*/
        action_output += "&&&&&&&&& You are in the Room "
                + to_string(this->d->player.getCurrentRoom()->getIndex())
                + " &&&&&&&&&\n";

        vector<Object*> room_objects = this->d->player.getCurrentRoom()->getObjects();
        int isMonster = 0, obj_size = room_objects.size();
        int monsterNum = 0, chestNum = 0, npcNum = 0;

        for(int i=0; i<obj_size; i++){
            action_output += "(" + to_string(i+1) + ") ";
            if (room_objects[i]->getTag() == "Monster"){
                action_output += "Fight with " + room_objects[i]->getName() + "\n";
                isMonster = 1;
                monsterNum += 1;
            }
            else if (room_objects[i]->getTag() == "NPC"){
                action_output += "Talk to " + room_objects[i]->getName() + "\n";
                npcNum += 1;
            }
            else if(room_objects[i]->getTag() == "Chest"){
                Chest* cc = dynamic_cast<Chest*> (room_objects[i]);
                action_output += "Open the " + room_objects[i]->getName();
                if (cc->getIsOpen() == true){
                    action_output += " (opened)\n";
                }
                else{
                    action_output += "\n";
                }
                chestNum += 1;
            }
        }
        if (isMonster == 0){
            action_output += "(" + to_string(obj_size+1) + ") Move out of the room\n"
                + "(" + to_string(obj_size+2) + ") Save to file\n"
                + "(" + to_string(obj_size+3) + ") Equip Item\n";
            this->allowAct = 3;
            this->npcNum = npcNum;
            this->chestNum = chestNum;
            this->monsterNum = monsterNum;
        }
        else{
            action_output += "(" + to_string(obj_size+1) + ") Save to file\n"
                + "(" + to_string(obj_size+2) + ") Equip Item\n";
            this->allowAct = 2;
            this->npcNum = npcNum;
            this->chestNum = chestNum;
            this->monsterNum = monsterNum;
        }


        ui->txtBrowserActionMenu->setText(s2q(action_output));

        if (isMonster == 1){
            ui->btnMoveOutRoom->setEnabled(false);
        }
        else{
            ui->btnMoveOutRoom->setEnabled(true);
        }

        this->status = "Menu";
    }
}

/*Convertor*/
string MainWindow::q2s(const QString & qs){
    return string((const char *)qs.toLocal8Bit());
}

QString MainWindow::s2q(const string & ss){
    return QString(QString::fromStdString(ss));
}

bool MainWindow::checkGameLogic()
{
    Monster* demon = dynamic_cast<Monster*>(this->d->getRoomPointer()->back().getObjects()[0]);
    if (this->d->player.checkIsDead() == true || demon->checkIsDead() == true){
        ui->txtBrowserActionMenu->setFontWeight(QFont::Black);
        ui->txtBrowserActionMenu->setFontPointSize(18);
        if (this->d->player.checkIsDead() == true){
            ui->txtBrowserActionMenu->setText("You dead!!!!!\nYour soul has been swallowed by the deep, bark dungeon...QQ");

        }
        else{
            ui->txtBrowserActionMenu->setText("You walk through the dungeon\n"
                                              "And SURVIVE!!\n"
                                              "You even beat the KING OF DUNGEON!!\n"
                                              "Your story will be talked by the songers\n"
                                              "But the horror is always deep in your heart...\n"
                                              "Congratulation...");
        }
        ui->btnChooseAction->setEnabled(false);
        ui->btnMoveOutRoom->setEnabled(false);
        ui->btnOpenBag->setEnabled(false);
        ui->btnPlayerInput->setEnabled(false);
        ui->btnSaveFile->setEnabled(false);
        return false;
    }
    return true;
}



void MainWindow::on_btnPlayerInput_clicked()
{
    string input = q2s(ui->lineEditPlayerDifficulty->text());

    if (input == "load"){
        this->d = new Dungeon;
        Record record;
        try{
            record.loadFromFile(&(d->player), *(this->d->getRoomPointer()), *(this->d->getWholeNPCAddress()), *(this->d->getWholeMonsterAddress()), *(this->d->getWholeChestAddress()));
            this->d->loadGameGUI();
            ui->statusBar->showMessage("Success Load the File!!");

            ui->btnPlayerInput->setEnabled(false);
            this->renewActionBag();
        }
        catch(CantFindTheLoadFile a){
            ui->statusBar->showMessage("Can't Find the " + s2q(a.getType()) + " File");
        }
    }
    else
    {
        string player_name = "";
        int difficulty = 0, valid_input = 1;

        for (int i=0; i<input.length(); i++){
            player_name += input[i];
            if (input[i] == 'D' && input[i+1] == 'i' && input[i+2] == 'f' && input[i+3] == 'i'){
                player_name.resize(player_name.length()-2);
                difficulty = input[i+5] - '0' - 1;
                break;
            }
            if (i == input.length()-1){
                valid_input = 0;
            }
        }

        if (valid_input == 0 || difficulty >= 4 || difficulty < 0){
            ui->lineEditPlayerDifficulty->setText("Invalid Input");
        }
        else{
            ui->lineEditPlayerDifficulty->setText("");

            this->d = new Dungeon();

            /*Create player*/
            this->d->createPlayer(player_name, difficulty);
            string player_information = "";

            player_information = this->d->player.getInformation();

            ui->txtBrowserPlayerInformation->setText(s2q(player_information));

            if (this->d->createMap()){
                ui->statusBar->showMessage("Success Generate the Dungeon!\n"
                                                             "Now we have " + s2q(to_string(this->d->getRoomLength())) + " Room !");
                this->d->player.setCurrentRoom(this->d->getRoomAddresses()[0]);
                this->d->player.setPreviousRoom(this->d->getRoomAddresses()[0]);
            }
            else{
                ui->statusBar->showMessage("Something Wrong!! Please recreate the player!!");
            }

            ui->statusBar->showMessage("Success Generate the Dungeon!\n"
                                                         "Now we have " + s2q(to_string(this->d->getRoomLength())) + " Room !");

            if (this->d->getRoomPointer()->back().getObjects()[0]->getName() != "KING OF DUNGEON"){
                ui->statusBar->showMessage("The KING OF DUNGEON have left the dungeon"
                                           "Please try another round.");
            }

            ui->btnPlayerInput->setEnabled(false);
            this->renewActionBag();
        }
    }

}

void MainWindow::on_btnChooseAction_clicked()
{
    int act = 0;
    if (this->status == "Menu"){
        string aact = q2s(ui->lineEditAction->text());

        if (!atoi(aact.c_str())){
            ui->lineEditAction->setText("Do not touch, Boy");
        }
        else{
            /*Depends on the action to set status*/
            act = stoi(aact);
            if (act > 0 && act <= this->monsterNum){
                this->status = "Fight";
                this->interactObject = act - 1;
                ui->lineEditAction->setText("");
                this->on_btnChooseAction_clicked();
            }
            else if (act > monsterNum && act <= this->monsterNum + this->npcNum){
                this->status = "Trade";
                this->interactObject = act - 1;
                ui->lineEditAction->setText("");
                this->on_btnChooseAction_clicked();
            }
            else if (act > this->monsterNum + this->npcNum && act <= monsterNum+npcNum+chestNum){
                this->status = "Chest";
                this->interactObject = act - 1;
                ui->lineEditAction->setText("");
                this->on_btnChooseAction_clicked();
            }
            else if (allowAct == 3){
                if (act == monsterNum+npcNum+chestNum+1){
                    this->status = "Move";
                    ui->lineEditAction->setText("");
                    this->on_btnChooseAction_clicked();
                }
                else if (act == monsterNum+npcNum+chestNum+2){
                    this->status = "Save";
                    ui->lineEditAction->setText("");
                    this->on_btnChooseAction_clicked();
                }
                else if (act == monsterNum+npcNum+chestNum+3){
                    this->status = "Bag";
                    ui->lineEditAction->setText("");
                    this->on_btnChooseAction_clicked();
                }
            }
            else if (allowAct == 2){
                if (act == monsterNum+npcNum+chestNum+1){
                    this->status = "Save";
                    ui->lineEditAction->setText("");
                    this->on_btnChooseAction_clicked();
                }
                else if (act == monsterNum+npcNum+chestNum+2){
                    this->status = "Bag";
                    ui->lineEditAction->setText("");
                    this->on_btnChooseAction_clicked();
                }
            }
            else {
                ui->lineEditAction->setText("Hey, Wrong Input!");
            }
        }
    }
    else{
        this->handleEvent();
    }
}


/*Judge the status and implementate the Action*/
void MainWindow::handleEvent()
{
    string output = "";
    // for the move of player
    if (this->status == "Move")
    {
        ui->btnOpenBag->setEnabled(false);
        ui->btnMoveOutRoom->setEnabled(false);
        ui->btnSaveFile->setEnabled(false);
        output += "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
        output += "Move: You are in the Room " + to_string(this->d->player.getCurrentRoom()->getIndex()) + "\n";
        output += "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
        Room* cur_room = this->d->player.getCurrentRoom();

        vector<int> direction;
        string deri[4] = {"Up", "Right", "Down", "Left"};
        if (cur_room->getUpRoom() != nullptr){
            direction.push_back(0);
        }
        if (cur_room->getRightRoom() != nullptr){
            direction.push_back(1);
        }
        if (cur_room->getDownRoom() != nullptr){
            direction.push_back(2);
        }
        if (cur_room->getLeftRoom() != nullptr){
            direction.push_back(3);
        }

        for(int i=0; i<direction.size(); i++){
            output +=  to_string(i+1) + ". Go " + deri[direction[i]] + "\n";
        }

        ui->txtBrowserActionMenu->setText(s2q(output));

        this->status = "Move2";
    }
    else if (this->status == "Move2"){
        Room* cur_room = this->d->player.getCurrentRoom();

        vector<int> direction;
        if (cur_room->getUpRoom() != nullptr){
            direction.push_back(0);
        }
        if (cur_room->getRightRoom() != nullptr){
            direction.push_back(1);
        }
        if (cur_room->getDownRoom() != nullptr){
            direction.push_back(2);
        }
        if (cur_room->getLeftRoom() != nullptr){
            direction.push_back(3);
        }

        if(ui->lineEditAction->text().toInt() && ui->lineEditAction->text().toInt() <= direction.size() && ui->lineEditAction->text().toInt() > 0){
            int next = direction[ui->lineEditAction->text().toInt() - 1];
            switch(next){
            case 0: // go UP
                this->d->player.changeRoom(cur_room->getUpRoom());
                break;
            case 1: // go Right
                this->d->player.changeRoom(cur_room->getRightRoom());
                break;
            case 2: // go Down
                this->d->player.changeRoom(cur_room->getDownRoom());
                break;
            case 3:
                this->d->player.changeRoom(cur_room->getLeftRoom());
                break;
            default:
                break;
            }

            ui->statusBar->showMessage("Success move to Room " + s2q(to_string(this->d->player.getCurrentRoom()->getIndex())));
            ui->lineEditAction->setText("");

            ui->btnOpenBag->setEnabled(true);
            ui->btnMoveOutRoom->setEnabled(true);
            ui->btnSaveFile->setEnabled(true);

            this->renewActionBag();
        }
        else{
            ui->lineEditAction->setText("None Valid Input...");
        }
    }
    // handle the Save
    else if (this->status == "Save"){
        Record record;
        vector<Room> for_store_room = this->d->getWholeRoom();
        vector<Chest> for_store_chest = this->d->getWholeChest();
        vector<Monster> for_store_monster = this->d->getWholeMonster();
        vector<NPC> for_store_npc = this->d->getWholeNPC();
        record.saveToFile(&(this->d->player), for_store_room, for_store_npc, for_store_monster, for_store_chest);
        ui->lineEditAction->setText("");
        ui->statusBar->showMessage("Success Save the File!!");
        this->renewActionBag();
    }
    // handle the Bag
    else if (this->status == "Bag"){
        if (this->d->player.getInventoryAddress()->size() != 0){
            ui->btnOpenBag->setEnabled(false);
            ui->btnMoveOutRoom->setEnabled(false);
            ui->btnSaveFile->setEnabled(false);


            output += "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
            output += "Choose The item you want to equip in your inventory \n";
            output += "The max number of Equipment is " + to_string((int)LIMIT_OF_EQUIP) + "\n";
            output += "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
            this->ui->txtBrowserActionMenu->setText(s2q(output));
            this->status = "Bag2";
            this->ui->lineEditAction->setText("");

        }
        else{
            ui->statusBar->showMessage("You have nothing to wear up!!");
            this->renewActionBag();
        }
    }
    else if (this->status == "Bag2"){
        int want_equip = 0;
        if (ui->lineEditAction->text().toInt() && ui->lineEditAction->text().toInt() > 0 && ui->lineEditAction->text().toInt() <= this->d->player.getInventory().size()){
            want_equip = ui->lineEditAction->text().toInt()-1;

            vector<Item> player_item = this->d->player.getInventory();

            if (this->d->player.getEquipment().size() == LIMIT_OF_EQUIP){
                output += "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
                output += "Choose The item you want to equip in your inventory \n";
                output += "The max number of Equipment is " + to_string((int)LIMIT_OF_EQUIP) + "\n";
                output += "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
                output += "The number of the equipment hit the limit!\n"
                          "Please select an item to replace...\n";
                this->ui->txtBrowserActionMenu->setText(s2q(output));
                this->status = "Bag3";
                this->d->player.increaseStates(player_item[want_equip].getAtk(), player_item[want_equip].getDef(), player_item[want_equip].getHp());
                this->ui->lineEditAction->setText("");
                this->d->player.getInventoryAddress()->erase(this->d->player.getInventoryAddress()->begin() + want_equip);
                this->d->player.getEquipmentAddress()->push_back(player_item[want_equip]);
            }
            else{
                this->ui->statusBar->showMessage(s2q("Success Equip " + player_item[want_equip].getName()));
                this->d->player.increaseStates(player_item[want_equip].getAtk(), player_item[want_equip].getDef(), player_item[want_equip].getHp());
                this->ui->lineEditAction->setText("");
                this->d->player.getInventoryAddress()->erase(this->d->player.getInventoryAddress()->begin() + want_equip);
                this->d->player.getEquipmentAddress()->push_back(player_item[want_equip]);
                ui->btnOpenBag->setEnabled(true);
                ui->btnMoveOutRoom->setEnabled(true);
                ui->btnSaveFile->setEnabled(true);

                this->renewActionBag(); // end the Bag
            }

            // (1) push the item to Equipment
            // (2) if not limit -> renew()
            // (3) if hit limit -> Bag3
            //     - enter the item to remove in equipment
            //     - Erase the item and push it to inventory
            //     - renew()
            // (4) disable the button to prevent out procedure
            //     - will enable when the bag procedure terminate

        }
        else{
            ui->lineEditAction->setText("Wrong Input");
        }
    }
    // handle the bag is full
    else if (this->status == "Bag3"){
        int want_remove = 0;
        if (ui->lineEditAction->text().toInt() && ui->lineEditAction->text().toInt() > 0 && ui->lineEditAction->text().toInt() <= (int)LIMIT_OF_EQUIP){
            want_remove = ui->lineEditAction->text().toInt()-1;

            vector<Item> player_equip = this->d->player.getEquipment();

            this->d->player.increaseStates(-(player_equip[want_remove].getAtk()), -(player_equip[want_remove].getDef()), -(player_equip[want_remove].getHp()));

            this->d->player.getEquipmentAddress()->erase(this->d->player.getEquipmentAddress()->begin() + want_remove);
            this->d->player.getInventoryAddress()->push_back(player_equip[want_remove]);
            ui->lineEditAction->setText("");
            this->ui->statusBar->showMessage(s2q("Success Equip " + player_equip.back().getName()));
            ui->btnOpenBag->setEnabled(true);
            ui->btnMoveOutRoom->setEnabled(true);
            ui->btnSaveFile->setEnabled(true);
            this->renewActionBag();
        }
        else{
            ui->lineEditAction->setText("Wrong input");
        }
    }
    // handle the Chest
    else if (this->status == "Chest"){
        this->ui->lineEditAction->setText("");
        Chest* chest = dynamic_cast<Chest*>(this->d->player.getCurrentRoom()->getObjects()[interactObject]);

        vector<Object*> room_objects = this->d->player.getCurrentRoom()->getObjects();
        int isMonster = 0;

        for (int i=0; i<room_objects.size(); i++){
            if (room_objects[i]->getTag() == "Monster"){
                isMonster = 1;
                break;
            }
        }

        if (isMonster == 1){
            this->ui->statusBar->showMessage("There are still monster in the Room!!");
        }
        else if(chest->getIsOpen() == true){
            this->ui->statusBar->showMessage("the Chest has been opened!!");
        }
        else{
            chest->triggerEvent(&(this->d->player));
            this->ui->statusBar->showMessage("Success open the Chest~~");
        }
        this->renewActionBag();;
    }
    // handle the Fight
    // (1) Fight will end untill the monster or the player die
    else if (this->status == "Fight"){
        ui->btnOpenBag->setEnabled(false);
        ui->btnMoveOutRoom->setEnabled(false);
        ui->btnSaveFile->setEnabled(false);


        Monster* combat_monster = dynamic_cast<Monster*>(this->d->player.getCurrentRoom()->getObjects()[interactObject]);
        if (combat_monster->checkIsDead() == true){
            ui->lineEditAction->setText("");
            if (combat_monster->getName() != "KING OF DUNGEON"){
                this->d->player.getCurrentRoom()->popObject(combat_monster);
            }

            /*Give gold*/
            int gold = rand()%(this->d->player.getCurrentRoom()->getIndex() * 5) + 1;
            this->ui->statusBar->showMessage("You Win! You success beat " + s2q(combat_monster->getName())
                                             + " !! You earned " + s2q(to_string(gold)) + " coins.");
            this->d->player.setCoin(this->d->player.getCoin() + gold);

            ui->btnOpenBag->setEnabled(true);
            ui->btnMoveOutRoom->setEnabled(true);
            ui->btnSaveFile->setEnabled(true);

            this->renewActionBag();
        }
        else if(this->d->player.checkIsDead() == true){
            this->ui->statusBar->showMessage("You dead...");
            this->renewActionBag();
        }
        else{
            output += combat_monster->getInformation();
            output += "What you want to do?\n"
                    "(1) Normal Attack\n"
                    "(2) Use Skill\n"
                    "(3) Retreat to the previous room\n";
            ui->lineEditAction->setText("");

            string player_information = this->d->player.getInformation();
            ui->txtBrowserPlayerInformation->setText(s2q(player_information));

            this->ui->txtBrowserActionMenu->setText(s2q(output));
            this->status = "Fight2";
        }
    }
    // handle for attack, skill, and retreat
    else if (this->status == "Fight2"){
        if (ui->lineEditAction->text().toInt() && ui->lineEditAction->text().toInt() > 0 && ui->lineEditAction->text().toInt() <= 3){
            int act = ui->lineEditAction->text().toInt();
            Monster* combat_monster = dynamic_cast<Monster*>(this->d->player.getCurrentRoom()->getObjects()[interactObject]);

            switch(act){
            case 1:{ // for attack
                int player_take = this->d->player.getAtk() - combat_monster->getDef();
                int monster_take = combat_monster->getAtk() - this->d->player.getDef(), skill_cooldown = 0;;

                if (player_take < 0){
                    player_take = 1;
                }
                else if (monster_take < 0){
                    monster_take = 1;
                }

                combat_monster->takeDamage(player_take);
                this->d->player.takeDamage(monster_take);

                ui->statusBar->showMessage("You take " + s2q(to_string(monster_take)) + " damage from the Monster");


                // If skill has cooldown, -1
                skill_cooldown = this->d->player.getSkillCoolDown();
                if (skill_cooldown > 0){
                    this->d->player.setSkillCoolDown(skill_cooldown - 1);

                }

                // For going to another round of fight
                this->status = "Fight";
                this->handleEvent();
                break;
            }
            case 2:{ // for skill
                int player_skill = this->d->player.getSkill()
                        , skill_cooldown = this->d->player.getSkillCoolDown()
                        , dmg = 0, if_success = 0;
                if (skill_cooldown > 0){
                    ui->statusBar->showMessage("Your skill is in the cooldown!!"
                                               ", it needs " + s2q(to_string(skill_cooldown)) + " rounds to recover.");
                    ui->lineEditAction->setText("");
                    this->status = "Fight";
                    this->handleEvent();
                }
                else{
                    switch (player_skill) {
                    case 0:
                        dmg = this->d->player.getAtk() * 3;
                        d->player.setSkillCoolDown(2);
                        break;
                    case 1:
                        dmg = this->d->player.getAtk() * 4;
                        d->player.setSkillCoolDown(3);
                        break;
                    case 2:
                        if_success = rand()%2;
                    }

                    if (d->player.getSkill() != 2){
                        combat_monster->takeDamage(dmg);
                        ui->statusBar->showMessage("You did " + s2q(to_string(dmg)) + " damage to " + s2q(combat_monster->getName()));
                    }
                    else if (if_success == 0){
                        d->player.takeDamage(9999);
                        ui->statusBar->showMessage("Fail on using Dead Devide!"
                                                   "Your soul has been teared!!");
                    }
                    else if (if_success == 1){
                        dmg = 9999;
                        combat_monster->takeDamage(dmg);
                        ui->statusBar->showMessage("You did " + s2q(to_string(dmg)) + " damage to " + s2q(combat_monster->getName()));
                    }

                    // go for another round
                    this->status = "Fight";
                    this->handleEvent();
                }
                break;
            }
            case 3:{ // for retreat, an out

                this->d->player.changeRoom(this->d->player.getPreviousRoom());
                ui->statusBar->showMessage("You retreat to the last Room...");


                ui->btnOpenBag->setEnabled(true);
                ui->btnMoveOutRoom->setEnabled(true);
                ui->btnSaveFile->setEnabled(true);

                this->ui->lineEditAction->setText("");
                this->renewActionBag();
                break;
            }
            }
        }
        else{
            ui->lineEditAction->setText("Wrong Input");
        }
    }
    // handle the Trade with NPC
    else if (this->status == "Trade"){
        // disable the button
        ui->btnOpenBag->setEnabled(false);
        ui->btnMoveOutRoom->setEnabled(false);
        ui->btnSaveFile->setEnabled(false);

        srand(time(NULL));
        Player* player = dynamic_cast<Player*>(&(this->d->player));
        NPC* npc = dynamic_cast<NPC*>(player->getCurrentRoom()->getObjects()[interactObject]);
        vector<Item> commodity = npc->getCommodity();

        output += npc->getScript() + string("I am ") + npc->getName() + "\n"
                + "The transaction will cost you some money ~_~!!\n";

        output += "===========================\n";
        for (int i=0; i<commodity.size(); i++){
            output += "(" + to_string(i+1) + ") " + commodity[i].shortIntro() + "\n";
        }
        output += "===========================\n";
        output += "choose the Item you want to see the detail... (n to quit)\n";

        this->ui->lineEditAction->setText("");
        this->ui->txtBrowserActionMenu->setText(s2q(output));
        this->status = "Trade2";
    }
    else if (this->status == "Trade2"){
        int want_item = 0, cost_coin = 0;
        NPC* npc = dynamic_cast<NPC*>(this->d->player.getCurrentRoom()->getObjects()[interactObject]);
        if(ui->lineEditAction->text().toInt() && ui->lineEditAction->text().toInt() <= npc->getCommodity().size() && ui->lineEditAction->text().toInt() > 0){
            cost_coin = rand()%(10 * this->d->player.getCurrentRoom()->getIndex()) + this->d->player.getCurrentRoom()->getIndex();
            want_item = ui->lineEditAction->text().toInt() - 1;
            output += npc->getCommodity()[want_item].getInformation();
            output += "The item will cost " + to_string(cost_coin) + " coins\n"
                    + "Do you sureliy want to buy? (y / n)\n";

            this->cost_coin = cost_coin;
            this->want_item = want_item;
            ui->txtBrowserActionMenu->setText(s2q(output));
            ui->lineEditAction->setText("");
            this->status = "Trade3";
        }
        else if (ui->lineEditAction->text() == "n"){
            // quit, an out
            ui->lineEditAction->setText("");
            ui->btnOpenBag->setEnabled(true);
            ui->btnMoveOutRoom->setEnabled(true);
            ui->btnSaveFile->setEnabled(true);
            this->renewActionBag();
        }
        else{
            ui->lineEditAction->setText("Wrong Input");
        }
    }
    else if (this->status == "Trade3"){
        if (ui->lineEditAction->text() == "y" && this->d->player.getCoin() >= this->cost_coin){
            Player* player = dynamic_cast<Player*>(&(this->d->player));
            NPC* npc = dynamic_cast<NPC*>(this->d->player.getCurrentRoom()->getObjects()[interactObject]);
            vector<Item> commodity = npc->getCommodity();

            player->addItem(commodity[want_item]);
            commodity.erase(commodity.begin() + want_item);
            npc->setCommodity(commodity);
            player->setCoin(player->getCoin() - cost_coin);

            ui->lineEditAction->setText("");
            ui->statusBar->showMessage("You have bought " + s2q(player->getInventoryAddress()->back().getName()));

            /*renew the information of bag and player*/
            string player_information = player->getInformation()
                    , bag_information = "";

            for (int i=0; i<player->getInventoryAddress()->size(); i++){
                bag_information += player->getInventory()[i].shortIntro() + "\n";
            }

            ui->txtBrowserPlayerInventory->setText(s2q(bag_information));
            ui->txtBrowserPlayerInformation->setText(s2q(player_information));

            this->status = "Trade";
            this->handleEvent();
        }
        else if (ui->lineEditAction->text() == "n"){
            ui->lineEditAction->setText("");
            this->status = "Trade";
            this->handleEvent();
        }
        else if (this->d->player.getCoin() < this->cost_coin){
            ui->lineEditAction->setText("");
            ui->statusBar->showMessage("You don't have enough money...");
            this->status = "Trade";
            this->handleEvent();
        }
        else{
            this->ui->lineEditAction->setText("Wrong Input");
        }
    }
}

void MainWindow::on_btnMoveOutRoom_clicked()
{
    if (this->d != nullptr){
        this->status = "Move";
        this->handleEvent();
    }
}

void MainWindow::on_btnOpenBag_clicked()
{
    if (this->d != nullptr){
        this->status = "Bag";
        this->handleEvent();
    }
}

void MainWindow::on_btnSaveFile_clicked()
{
    if (this->d != nullptr){
        this->status = "Save";
        this->handleEvent();
    }
}

void MainWindow::on_btnAction1_clicked()
{
    if (this->d != nullptr){
        ui->lineEditAction->setText("1");
        this->on_btnChooseAction_clicked();
    }
}

void MainWindow::on_btnAction2_clicked()
{
    if (this->d != nullptr){
        ui->lineEditAction->setText("2");
        this->on_btnChooseAction_clicked();
    }
}

void MainWindow::on_btnAction3_clicked()
{
    if (this->d != nullptr){
        ui->lineEditAction->setText("3");
        this->on_btnChooseAction_clicked();
    }
}

void MainWindow::on_btnAction4_clicked()
{
    if (this->d != nullptr){
        ui->lineEditAction->setText("4");
        this->on_btnChooseAction_clicked();
    }
}

void MainWindow::on_btnAction5_clicked()
{
    if (this->d != nullptr){
        ui->lineEditAction->setText("5");
        this->on_btnChooseAction_clicked();
    }
}

void MainWindow::on_btnAction6_clicked()
{
    if (this->d != nullptr){
        ui->lineEditAction->setText("6");
        this->on_btnChooseAction_clicked();
    }
}

void MainWindow::on_btnActionYes_clicked()
{
    if (this->d != nullptr){
        ui->lineEditAction->setText("y");
        this->on_btnChooseAction_clicked();
    }
}

void MainWindow::on_btnActionNo_clicked()
{
    if (this->d != nullptr){
        ui->lineEditAction->setText("n");
        this->on_btnChooseAction_clicked();
    }
}
