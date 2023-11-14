#include "hpp-files/Game.hpp"
#include <iostream>
Game::Game()
{
    int xMax, yMax;
    getmaxyx(stdscr, yMax, xMax);
    yMax /= 2;
    xMax /= 2;

    WINDOW *menuwin = newwin(6, 102, yMax, xMax - 51);
    box(menuwin, 0, 0);

    WINDOW *win = newwin(20, 102, yMax - 20, xMax - 51);
    nodelay(win, true);

    logic = new Logic(win, menuwin);

    entitiesOBJ = logic->ReturnEntitiesOBJ();

    events = logic->ReturnEventsOBJ();

    gamestatus = Running;

    shop = new Negozio(win, entitiesOBJ);

    menu = new Menu(menuwin, win);

    logic->InitColors();
}

void Game::startGameLoop()
{
    bool endGame = false;

    initMenuWindow();

    while (!endGame)
    {
        updateVariables();

        menuChoice playerMenuChoice = (menuChoice)menu->finestraMenu();

        switch (playerMenuChoice)
        {
        case NewGame:
            initializeEntitiesForNewGame();
            runGame();
            break;
        case LoadGame:
            initializeEntitiesForLoadGame();
            runGame();
            break;
        case Shop:
            initializeEntitiesForShop();
            openShop();
            break;
        default:
            endGame = true;
            break;
        }
        wrefresh(win);
    }
}
