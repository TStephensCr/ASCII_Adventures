#include "Game.hpp"

int main()
{
    initscr();
    noecho();
    cbreak();
    start_color();
    curs_set(FALSE);
    timeout(0);

    Game *game = new Game();

    game->startGameLoop();

    endwin();
    return 0;
}
