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

    WINDOW * menuwin = newwin(6, 102, 22, 1);
    box(menuwin,0,0);

    WINDOW* win = newwin(20, 102, 0, 0);
    //keypad(win, true);
    nodelay(win, true);

    box(win, 0, 0);

    Logic* logica = new Logic(win, menuwin);

    Events* eventi = logica->ReturnEventsOBJ();

    GameStatus gamestatus = Game;
    
    Menu * menu = new Menu(menuwin, win);
    menu->titolo();
    menu->finestraGioco();
    bool endGame = false;
    while(!endGame){
        int scelta=menu->finestraMenu();
        if(scelta == 0){//gioco nuovo
            logica->InitMappa(1,2);
            gamestatus=Game;
            while (gamestatus==Game) {
                    int choice = eventi->getmv();
                    if(choice==27){
                        logica->FileWrite();
                        gamestatus=MenU;
                        menu->titolo();
                       
                    }
                    else{
                        logica->GiveDynamicity();

                        napms(NAPTIME); 

                        if(logica->ReturnInfoPlayer()->hp == 0){
                            logica->FileWrite();
                            gamestatus = MenU;
                            menu->GameOver();
                            logica->ReturnInfoPlayer()->hp=100;
                        }
                    }
                    wrefresh(win);               
            }
        }
        else if(scelta == 1){//gioco caricato
            
        }
        //Negozio* shop= new Negozio(win,menuwin);
        else if(scelta == 2){//negozio
            
        }
        else{//esci
            endGame = true;
        }
    }
    endwin();
    return 0;
}