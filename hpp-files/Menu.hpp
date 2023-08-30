#ifndef _MENU_H_
#define _MENU_H_
#include <ncurses.h>
#include <string>

class Menu{
    private:

        WINDOW* menuwin;
        WINDOW* inputwin;

    public:
        
        Menu(WINDOW *menuwin, WINDOW *inputwin);
        void titolo();
        int finestraMenu();
        void finestraGioco();
      
       
};
#endif