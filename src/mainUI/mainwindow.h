#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <QFontDialog>
#include "Dungeon.h"
#include "Item.h"
#include "Monster.h"
#include "NPC.h"
#include "Player.h"
#include "Chest.h"
#include "Exceptions.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    /*for the Actionmenu and Bag and check game logic*/
    void renewActionBag();

    /*Convertor*/
    string q2s(const QString&);
    QString s2q(const string&);

    /*Game End -- for gameover and win*/
    bool checkGameLogic();

private slots:
    /*To initialize the dungeon*/
    void on_btnPlayerInput_clicked();

    void on_btnChooseAction_clicked();

    void on_btnMoveOutRoom_clicked();

    void on_btnOpenBag_clicked();

    void on_btnSaveFile_clicked();

    void on_btnAction1_clicked();

    void on_btnAction2_clicked();

    void on_btnAction3_clicked();

    void on_btnAction4_clicked();

    void on_btnAction5_clicked();

    void on_btnAction6_clicked();

    void on_btnActionYes_clicked();

    void on_btnActionNo_clicked();

private:
    Ui::MainWindow *ui;
    Dungeon *d;

    /*For the event handle (dealing with the action btn)*/
    void handleEvent();

    /*Record the status of dungeon*/
    //enable time later click
    //type: "Menu", "Fight", "Trade", "Move", "Bag", "Save", "Chest"
    //both of action has like: "Move", "Move1" to specify the level of it
    string status;

    /*for the use of judging the action*/
    //associate with the "Menu" status
    //automatically renew when the renew() call
    int allowAct;
    int monsterNum;
    int npcNum;
    int chestNum;

    // use this to record who you want to fight, trade
    int interactObject;
    int want_item;
    int cost_coin;
};

#endif // MAINWINDOW_H
