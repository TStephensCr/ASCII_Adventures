#ifndef _MAPPA_H_
#define _MAPPA_H_
#define xMaxG 100
#define yMaxG 18

#include <ncurses.h>

class Mappa{
    public:
    Mappa(WINDOW* win);
    void stampamappa(WINDOW* playwin);
    void leggimappa(char curmap);

    private:
    WINDOW* playwin;
    char Matrice[yMaxG][xMaxG];
};

#endif