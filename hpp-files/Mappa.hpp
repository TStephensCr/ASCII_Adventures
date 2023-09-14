#ifndef _MAPPA_H_
#define _MAPPA_H_
#define xMaxG 100
#define yMaxG 18
#include <ncurses.h>


class Mappa{
    public:
    Mappa(WINDOW* win);
    void stampamappa();//scrive su schermo la mappa contenuta nella matrice
    void leggimappa(char curmap);//legge una mappa data in input dal file e la mette in una matrice
    void mapcaller(char curmap);//gestisce quale mappe vengono lette/scritte/cancellate, forse sarà inutile come funzione, nel caso la tolgo

    private:
    WINDOW* playwin;
    char Matrice[xMaxG][yMaxG];
};

#endif