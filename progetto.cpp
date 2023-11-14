#include "hpp-files/Game.hpp"
#include <iostream>
int main()
{
    initscr();
    noecho();
    cbreak();
    start_color();
    curs_set(FALSE);

    Game *game = new Game();

    game->startGameLoop();

    endwin();
    return 0;
}
