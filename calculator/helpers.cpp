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


template<typename T>
T VectorStack<T>::pop()
{
    T value = stack.top();
    stack.pop_back();
    return value;
}
