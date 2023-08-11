#include <ncurses.h>
#include <curses.h>

#include "Mappa.cpp"/*
#include "Menu.hpp" 
#include "GameLogic/Logic.cpp"*/


int main(){
    initscr();
    noecho();
    cbreak();
    curs_set(false);
    getch();
    WINDOW * menuwin = newwin(yMax, xMax-2, 30, 1);
    WINDOW * inputwin = newwin(yMax-15, xMax-10, 3, 5);
    box(inputwin,0,0);
    nodelay(inputwin, true);
    //Menu oggetto
    Mappa * m = new Mappa(inputwin);
    int yMaxG,xMaxG;
    getmaxyx(inputwin,yMaxG,xMaxG);
    //Stampa mappa
    //resizeterm(105,105);
    m->stampamappa(inputwin);
    wgetch(inputwin);
    wgetch(inputwin);
    getch();
    endwin();
    return 0;
}
