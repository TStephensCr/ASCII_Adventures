#include <ncurses.h>
#include <string>
#include <cstdlib>
#include <ctime>
#include <time.h>
#include <stdlib.h>
#include <iostream>
#include "Mappa.cpp"/*
#include "Menu.hpp" 
#include "GameLogic/Logic.cpp"*/


int main(){
    initscr();
    noecho();
    cbreak();
    curs_set(false);

    WINDOW * menuwin = newwin(yMax, xMax-2, 30, 1);
    WINDOW * inputwin = newwin(yMax-15, xMax-10, 3, 5);
    nodelay(inputwin, true);
    refresh();
    //Menu oggetto
    Mappa * m = new Mappa(inputwin);
    int yMaxG,xMaxG;
    getmaxyx(inputwin,yMaxG,xMaxG);
    //Stampa mappa
    resizeterm(105,105);
    m->stampamappa(inputwin);
    wrefresh(inputwin);
    getch();
    getch();

}
