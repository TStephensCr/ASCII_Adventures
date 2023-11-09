#include <ncurses.h>
#include "hpp-files/Logic.hpp"
#include "hpp-files/Mappa.hpp"
#include "hpp-files/Menu.hpp" 
#include "hpp-files/Negozio.hpp"

int main() {
    initscr();
    noecho();
    cbreak();
    start_color();
    curs_set(FALSE);

    int xMax, yMax;
    getmaxyx(stdscr, yMax, xMax);
    yMax/=2;
    xMax/=2;

    WINDOW * menuwin = newwin(6, 102, yMax, xMax-51);
    box(menuwin,0,0);

    WINDOW* win = newwin(20, 102, yMax-20, xMax-51);
    //keypad(win, true);
    nodelay(win, true);

    box(win, 0, 0);

    Logic* logica = new Logic(win, menuwin);

    logica->InitColors();

    Entities* entitiesOBJ = logica->ReturnEntitiesOBJ();

    Events* eventi = logica->ReturnEventsOBJ();

    GameStatus gamestatus = Game;

    Negozio* shop= new Negozio(win, entitiesOBJ);
    
    Menu * menu = new Menu(menuwin, win);
    menu->titolo();
    menu->finestraGioco();
    bool endGame = false;

    while(!endGame){
        int scelta=menu->finestraMenu();
        if(scelta == 0){//gioco nuovo
            logica->ResetEntities();
            logica->InitEntities();
            logica->InitMappa(1,0);
            gamestatus=Game;
            logica->set_dev_mode(0);
            while (gamestatus==Game) {
                    int choice = eventi->getmv();
                    if(choice==27){
                        menu->titolo();
                        logica->FileWrite();
                        gamestatus=MenU;
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
            logica->ResetEntities();
            logica->FileRead();
            logica->InitMappa(logica->returnCurMap(),logica->returnCurLev());
            gamestatus=Game;
            while (gamestatus==Game) {
                    int choice = eventi->getmv();
                    if(choice==27){
                        menu->titolo();
                        logica->FileWrite();
                        gamestatus=MenU;
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
        else if(scelta == 2){//negozio
            logica->ResetEntities();
            logica->FileRead();
            logica->InitMappa(10, 0);
            int choice;
            gamestatus = Game;
            while(gamestatus==Game){
                entitiesOBJ->DisplayPlayerStats();
                choice = shop->create_Shop();
                shop->eventiShop(choice);
                if(choice==-1){
                        logica->InitMappa(0,0);
                        logica->FileWrite();
                        gamestatus=MenU;
                }
            }
            wrefresh(win);
        }
        else{//esci
            endGame = true;
        }
    }
    endwin();
    return 0;
}
