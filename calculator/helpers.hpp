#ifndef HELPERS_H_
#define HELPERS_H_

#include <string>
#include <ncurses.h>


class Window
{
public:
    WINDOW *window;

    inline Window(int y_size, int x_size, int y_pos, int x_pos) {
        window = newwin(y_size, x_size, y_pos, x_pos);
    }
    inline ~Window() { delwin(window); }

    inline void move(int y, int x) { wmove(window, y, x); }
    inline void print(const std::string& str) { wprintw(window, "%s", str.c_str()); }
    inline void refresh() { wrefresh(window); }
    inline void set_keypad(bool is_enable) { keypad(window, is_enable); }
    inline void clear_line() { wclrtoeol(window); }
    inline int getkey() { return wgetch(window); }
};


enum KeyCode
{
    CTRL_A = 1,
    CTRL_B = 2,
    CTRL_E = 5,
    CTRL_F = 6,
    CTRL_H = 8,
    CTRL_K = 11,
    ENTER = 13,
    CTRL_U = 21,
};


void init_ncurses();

#endif // HELPERS_H_
