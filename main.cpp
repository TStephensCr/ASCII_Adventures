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
    WINDOW * menuwin = newwin(5, 102, 22, 1);
    box(menuwin,0,0);
    WINDOW * inputwin = newwin(20, 102, 1, 1);
    box(inputwin,0,0);
    wrefresh(menuwin);
    wrefresh(inputwin);
    //nodelay(inputwin, true);

    //Menu oggetto
    Mappa * m = new Mappa(inputwin);

    //Stampa mappa
    m->leggimappa('2');
    m->stampamappa(inputwin);
    wgetch(inputwin);
    endwin();
}
