#ifndef _MAPPA_H_
#define _MAPPA_H_
#define xMax 100
#define yMax 100

#include <ncurses.h>

class Mappa{
    public:
    Mappa(WINDOW* win);
    void stampamappa(WINDOW* playwin);

    private:
    WINDOW* playwin;
    char Matrice[yMax][xMax];
};

#endif