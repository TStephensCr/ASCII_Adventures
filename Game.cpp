#include "hpp-files/Game.hpp"
#include <iostream>

Game::Game(){
    int xMax, yMax;
    getmaxyx(stdscr, yMax, xMax);
    yMax/=2;
    xMax/=2;

    WINDOW * menuwin = newwin(6, 102, yMax, xMax-51);
    box(menuwin,0,0);

    WINDOW* win = newwin(20, 102, yMax-20, xMax-51);
    nodelay(win, true);

    logic = new Logic(win, menuwin);

    entitiesOBJ = logic->ReturnEntitiesOBJ();

    events = logic->ReturnEventsOBJ();

    gamestatus = Running;

    shop = new Negozio(win, entitiesOBJ);
    
    menu = new Menu(menuwin, win);

    logic->InitColors();
}


void Game::initMenuWindow(){
    menu->titolo();
    menu->finestraGioco();
}

void Game::startGameLoop(){

    bool endGame = false;

    initMenuWindow();

    while(!endGame){
        int scelta = menu->finestraMenu();

        switch (scelta)
        {
            case 0:
                initializeEntitiesForNewGame();
                runGame();
                break;
            case 1:
                initializeEntitiesForLoadGame();
                runGame();
                break;
            case 2:
                openShop();
                break;
            default:
                endGame = true;
                break;
        }
        wrefresh(win);
    }   
}

void Game::runGame(){
    gamestatus = Running;

    logic->set_dev_mode(0);

    while (gamestatus == Running) {

            int playerKeyPressed = events->getmv();

            if(playerKeyPressed == ESC_KEY){
                menu->titolo();
                logic->FileWrite();
                gamestatus=MenU;
            }
            else{
                logic->GiveDynamicity();

                checkEndGame();

                napms(NAPTIME); 
            }

            wrefresh(win);               
    }
}



void Game::openShop(){
    logic->ResetEntities();
    logic->FileRead();
    logic->InitMappa(10, 0, false);
    int choice;
    gamestatus = Shopping;
    while(gamestatus == Shopping){
        entitiesOBJ->DisplayPlayerStats();
        choice = shop->create_Shop();
        shop->eventiShop(choice);
        if(choice==-1){
                logic->InitMappa(0,0, false);
                logic->FileWrite();
                gamestatus=MenU;
        }
    }
    wrefresh(win);
}

void Game::checkEndGame(){
    if(logic->ReturnInfoPlayer()->hp == 0){
        logic->FileWrite();
        gamestatus = MenU;
        menu->GameOver();
        logic->ReturnInfoPlayer()->hp=100;
    }
}

void Game::initializeEntitiesForNewGame(){
    logic->ResetEntities();

    logic->InitEntities();

    logic->InitMappa(1,0, true);
}

void Game::initializeEntitiesForLoadGame(){
    logic->ResetEntities();

    logic->FileRead();

    logic->InitMappa(logic->returnCurMap(),logic->returnCurLev(), true);
}