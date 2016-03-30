#include <ncurses.h>

int main(){
    initscr();
    cbreak();
    printw("Hellow trwert");
    refresh();
    getchar();
    endwin();
    return 0;
}
