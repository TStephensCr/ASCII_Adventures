#include "hpp-files/Game.hpp"

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

