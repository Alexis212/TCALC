#include "helpers.hpp"
#include <ncurses.h>


void init_ncurses()
{
    initscr();
    cbreak();
    keypad(stdscr, true);
    noecho();
    // clear();
    // refresh();
}


template<typename T>
T VectorStack<T>::pop()
{
    T value = stack.top();
    stack.pop_back();
    return value;
}

// mvprintw(row, max_cols/2 - str.length()/2, "%s", str.c_str());
