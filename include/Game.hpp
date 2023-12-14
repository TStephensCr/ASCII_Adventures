#pragma once
#include "Logic.hpp"
#include "Menu.hpp"
#include "Market.hpp"

class Game
{
protected:
    WINDOW *menuwin;

    WINDOW *win;

    Logic *logic;

    Entities *entitiesOBJ;

    Events *events;

    Negozio *shop;

    Menu *menu;

    GameStatus gamestatus;

    int curmap_ = 1;

    int curLev_ = 0;

    int maxScreenX, maxScreenY;

private:
    void updateVariables();

    void initMenuWindow();

    void runGame();

    void openShop();

    void checkEndGame();

    void initializeEntitiesForNewGame();

    void initializeEntitiesForLoadGame();

    void initializeEntitiesForShop();

    void returnToMenu();

public:
    Game();

    void startGameLoop();
};
