#include "hpp-files/Game.hpp"

void Game::initMenuWindow()
{
    menu->titolo();
    menu->finestraGioco();
}

void Game::runGame()
{
    gamestatus = Running;

    logic->set_dev_mode(0);

    while (gamestatus == Running)
    {

        int playerKeyPressed = events->getmv();

        if (playerKeyPressed == ESC_KEY)
        {
            initMenuWindow();
            logic->FileWrite();
            gamestatus = MenU;
        }
        else
        {
            logic->update_game_logic();

            logic->render();

            checkEndGame();

            napms(NAPTIME);
        }

        wrefresh(win);
    }
}

void Game::openShop()
{
    logic->ResetEntities();
    logic->FileRead();
    logic->InitMappa(10, 0, false);
    int choice;
    gamestatus = Shopping;
    while (gamestatus == Shopping)
    {
        entitiesOBJ->DisplayPlayerStats();
        choice = shop->create_Shop();
        shop->eventiShop(choice);
        if (choice == -1)
        {
            initMenuWindow();
            logic->FileWrite();
            gamestatus = MenU;
        }
    }
    wrefresh(win);
}

void Game::checkEndGame()
{
    if (logic->ReturnInfoPlayer()->hp == 0)
    {
        logic->FileWrite();
        gamestatus = MenU;
        menu->GameOver();
        logic->ReturnInfoPlayer()->hp = 100;
    }
}

void Game::initializeEntitiesForNewGame()
{
    logic->ResetEntities();

    logic->InitEntities();

    logic->InitMappa(1, 0, true);
}

void Game::initializeEntitiesForLoadGame()
{
    logic->ResetEntities();

    logic->FileRead();

    logic->InitMappa(logic->returnCurMap(), logic->returnCurLev(), true);
}