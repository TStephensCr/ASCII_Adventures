#include "hpp-files/Game.hpp"

void Game::initMenuWindow()
{
    menu->titolo();
    menu->finestraGioco();
}

void Game::updateVariables()
{
    curmap_ = logic->returnCurMap();
    curLev_ = logic->returnCurLev();
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
            returnToMenu();
        }
        else
        {
            logic->update_game_logic();

            logic->render();

            checkEndGame();

            napms(NAPTIME);
        }
    }
}

void Game::openShop()
{
    gamestatus = Shopping;

    int choice;

    while (gamestatus == Shopping)
    {
        entitiesOBJ->DisplayPlayerStats();

        choice = shop->create_Shop();

        shop->eventiShop(choice);

        logic->FileWrite();

        if (choice == -1)
        {
            returnToMenu();
        }
    }
    wrefresh(win);
}

void Game::checkEndGame()
{
    if (logic->ReturnInfoPlayer()->hp <= 0)
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

    logic->initEntities();

    logic->scrambleArray();

    logic->InitMappa(1, 0, true);

    logic->setNewGame(1, 1);
}

void Game::initializeEntitiesForLoadGame()
{
    logic->ResetEntities();

    logic->FileRead();

    logic->InitMappa(logic->returnMapCounter(), logic->returnCurLev(), true);

    logic->setNewGame(logic->returnDifficulty(), logic->returnMapCounter());
}

void Game::initializeEntitiesForShop()
{
    logic->ResetEntities();

    logic->FileRead();

    logic->InitMappa(10, 0, false);
}

void Game::returnToMenu()
{
    initMenuWindow();

    logic->FileWrite();

    gamestatus = MenU;
}