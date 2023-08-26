#include <ncurses.h>
#include "hpp-files/Logic.hpp"
#include "P.project2023/Mappa.cpp"

int main() {
    initscr();
    noecho();
    cbreak();
    start_color();
    curs_set(FALSE);

    int x, y;
    getmaxyx(stdscr, y, x);

    WINDOW* win = newwin(y, x, 0, 0);

    nodelay(win, true);

    box(win, 0, 0);

    Mappa * m = new Mappa(win);

    Logic* logica = new Logic(win);

    Entities* entita = logica->ReturnEntitiesOBJ();

    Events* eventi = logica->ReturnEventsOBJ();

    ens j = entita->Insert(player,4,4);

    m->leggimappa('3');

    m->stampamappa(win);

    while (1) {

        int choice = eventi->getmv();

        if (choice == 'q') // 'q' key to quit the game
            break;

        logica->GiveDynamicity();
        
        napms(NAPTIME); 
    }

    endwin();
    return 0;
}