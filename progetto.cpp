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
    if(scelta == 0){//gioco
        logica->InitMappa(1, 0);

        while (1) {
            if(gamestatus == Game){
                int choice = eventi->getmv();
            
                logica->GiveDynamicity();

                napms(NAPTIME); 
            }

            if(logica->ReturnInfoPlayer()->hp == 0){
                gamestatus = MenU;
                menu->GameOver();
                wrefresh(win);
                int scelta=menu->finestraMenu();
            }
        }
    }
    else if(scelta == 1){
        //qui c'è da pensare: la scelta non la possiamo mettere nel ciclo infinito del gioco, ma senno come si fa a uscire e entrare tra il gioco e il menu?
    }
    else{
        //sta opzione non so neanche che farci onesto
    }

    endwin();
    return 0;
}