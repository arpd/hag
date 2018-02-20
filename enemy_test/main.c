#include <ncurses.h>
#include <unistd.h>

#include "map.h"
#include "list.h"
#include "enemy.h"

#define W 60
#define H 13

char* map[] = {
"           +++++++++++++++++++++++++++++++++++++++++++++++++",
"           +................................+..............+",
"           +...............................................+",
"           +..+.............................+..............+",
"++++++++++++..+++++++++++++++++++++++++++++++..............+",
"+.............+                             +..............+",
"+..++++++++++++                             +..............+",
"+..+++++++                                  +..............+",
"+..++....+                                  +..............+",
"++..+....+                                  +..............+",
" +.......+                                  +.....++++.....+",
" +.......+                                  +.....+........+",
" +++++++++                                  ++++++++++++++++"};

int main(int argc, char *argv[]) {
    
    int x = 50, y = 4;
    int max_y = 0, max_x = 0;

    initscr();
    noecho();
    curs_set(0);
    WINDOW *my_win = newwin(10, 10, 20, 20);
    map_load(map, W, H);
    enemy_add(0, 'X', 5, 9, 51);
    enemy_add(0, 'X', 5, 2, 49);
    enemy_add(0, 'X', 5, 11, 8);

    while(1) {
        refresh();
        wclear(my_win);
        map_print(my_win, y, x);
        enemy_draw(my_win, y, x);
        mvwprintw(my_win, 5, 5, "o");
        wrefresh(my_win);
        int xn = x, yn = y;
        int ch = ERR;
        if (ch = getch(), ch != ERR) {
            switch (ch) {
                case 'j':
                    yn++;
                    break;
                case 'k':
                    yn--;
                    break;
                case 'h':
                    xn--;
                    break;
                case 'l':
                    xn++;
                    break;
            }
        }
        enemy_t *at = enemy_at(yn, xn);
        if (map_get(yn, xn) == '.') {
            if (at) {
                enemy_hurt(at, 1);
            } else {
                x = xn;
                y = yn;
            }
        } 
    }

    endwin();
}
