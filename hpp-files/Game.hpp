#include <ncurses.h>
#include "Logic.hpp"
#include "Mappa.hpp"
#include "Menu.hpp" 
#include "Negozio.hpp"

class Game{
    protected:
        WINDOW * menuwin;

        WINDOW* win;

        Logic* logic;

        Entities* entitiesOBJ;

        Events* events;

        Negozio* shop;

        Menu* menu;

        GameStatus gamestatus;

        int maxScreenX, maxScreenY;
    private:
        void initMenuWindow();

        void runGame();

        void openShop();

        void checkEndGame();

        void initializeEntitiesForNewGame();

        void initializeEntitiesForLoadGame();
    public:
        Game();

        void startGameLoop();


};