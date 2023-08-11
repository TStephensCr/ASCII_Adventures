#include <ncurses.h>
using namespace std;

int main() {
    initscr();
    noecho();
    cbreak();
    start_color();
    curs_set(FALSE);

    int x, y;
    getmaxyx(stdscr, y, x);

    WINDOW* win = newwin(y, x, 0, 0);

    nodelay(win, true);

    box(win, 0, 0);

    while(1){
        wgetch(win);
    }
    

    endwin();
    return 0;
}
