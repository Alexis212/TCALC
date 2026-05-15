#include "helpers.hpp"
#include <ncurses.h>


void init_ncurses()
{
    initscr();
    cbreak();
    // raw();
    nonl();
    keypad(stdscr, true);
    noecho();
    // clear();
    // refresh();
}
