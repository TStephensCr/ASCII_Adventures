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

    WINDOW * menuwin = newwin(5, 102, 22, 1);
    box(menuwin,0,0);

    WINDOW* win = newwin(20, 102, 0, 0);
    //keypad(win, true);
    nodelay(win, true);

    box(win, 0, 0);

    Logic* logica = new Logic(win);

    Entities* entita = logica->ReturnEntitiesOBJ();

    Events* eventi = logica->ReturnEventsOBJ();

    GameStatus gamestatus = Game;

    Menu * menu = new Menu(menuwin, win);
    menu->titolo();
    menu->finestraGioco();
    int scelta=menu->finestraMenu();

    logica->InitMappa('1', 2);

    while (1) {
        if(gamestatus == Game){
            int choice = eventi->getmv();
        
            logica->GiveDynamicity();

            napms(NAPTIME); 
        }

        if(logica->ReturnInfoPlayer()->hp == 0){
            menu->GameOver();
            gamestatus = MenU;
            wrefresh(win);
        }
    }

    endwin();
    return 0;
}