#include <ncurses.h>
#include "Logic.hpp"
#include "Mappa.hpp"
#include "Menu.hpp"
#include "Negozio.hpp"

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