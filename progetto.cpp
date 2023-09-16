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
    while(1){
        int scelta=menu->finestraMenu();
        if(scelta == 0){//gioco
            logica->InitMappa(5, 0);
            gamestatus=Game;
            while (gamestatus==Game) {
                    int choice = eventi->getmv();
                    if(choice==27){
                        gamestatus=MenU;
                        menu->titolo();
                        wrefresh(win);
                    }
                    else{
                        logica->GiveDynamicity();

                            napms(NAPTIME); 

                        if(logica->ReturnInfoPlayer()->hp == 0){
                            gamestatus = MenU;
                            menu->GameOver();
                            wrefresh(win);
                            //serve un anti-InitEntities
                            //serve un annullatore del save
                        }
                        }
                            
            }
        }
        else if(scelta == 1){
            //qui c'è da pensare: la scelta non la possiamo mettere nel ciclo infinito del gioco, ma senno come si fa a uscire e entrare tra il gioco e il menu?
        }
        else{
            //sta opzione non so neanche che farci onesto
        }
    }
    endwin();
    return 0;
}