#include <ncurses.h>
#include "hpp-files/Logic.hpp"
#include "hpp-files/Mappa.hpp"
#include "hpp-files/Menu.hpp" 

int main() {
    initscr();
    noecho();
    cbreak();
    start_color();
    curs_set(FALSE);

    int x, y;
    getmaxyx(stdscr, y, x);

    WINDOW * menuwin = newwin(5, 102, 22, 1);
    box(menuwin,0,0);

    WINDOW* win = newwin(20, 102, 0, 0);
    //keypad(win, true);
    nodelay(win, true);

    box(win, 0, 0);

    Mappa * m = new Mappa(win);

    Logic* logica = new Logic(win);

    Entities* entita = logica->ReturnEntitiesOBJ();

    Events* eventi = logica->ReturnEventsOBJ();

    Menu * menu = new Menu(menuwin, win);
    menu->titolo();
    menu->finestraGioco();
    int scelta=menu->finestraMenu();

    m->mapcaller();

    m->stampamappa();

    logica->InitEntities(4);

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