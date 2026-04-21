#include "helpers.hpp"
#include <ncurses.h>
#include <string>
#include <sstream>
#include <cstdlib>
#include <stdexcept>


int main(int argc, char *argv[])
{
    const std::string title = "TCALC: A SIMPLE TERMINAL CALCULATOR";
    const std::string prompt = "  > ";

    VectorStack<double> stack;
    std::string buffer;

    init_ncurses();

    int max_rows, max_cols;
    getmaxyx(stdscr, max_rows, max_cols);

    // Title Windows
    Window title_window = Window(3, max_cols, 0, 0);
    title_window.move(1, max_cols/2 - title.length()/2);
    title_window.print(title);
    title_window.refresh();

    // Console Windows
    Window console_window = Window(max_rows - 3, max_cols, 3, 0);
    console_window.set_keypad(true);

    int key, line = 0;
    bool is_exit = false;
    while (true)
    {
        buffer = "";
        int cursor = 0;

        while (true)
        {
            console_window.move(line, 0);
            console_window.clear_line();
            console_window.print(prompt + buffer);
            console_window.move(line, prompt.length() + cursor);

            key = console_window.getkey();

            if (key == KEY_BACKSPACE && !buffer.empty())
            {
                buffer.erase(buffer.begin() + cursor - 1);
                cursor -= 1;
            }

            else if (key == KEY_RIGHT || key == KeyCode::CTRL_F)
                cursor += 1;

            else if (key == KEY_LEFT || key == KeyCode::CTRL_B)
                cursor -= 1;

            else if (key == KeyCode::CTRL_A)
                cursor = 0;

            else if (key == KeyCode::CTRL_E)
                cursor = buffer.length();

            else if (key == KeyCode::CTRL_H)
            {
                buffer.erase(buffer.begin(), buffer.begin() + cursor);
                cursor = 0;
            }

            else if (key == KeyCode::CTRL_K)
                buffer.erase(buffer.begin() + cursor, buffer.end());

            // Check if key was printable character
            if (key >= 32 && key <= 255)
            {
                char char_key = char(key);

                if (std::isdigit(char_key))
                {
                    buffer.insert(buffer.begin() + cursor, char_key);
                    cursor += 1;
                }

                if (char_key == '\n')
                    break;

                if (char_key == 'q')
                {
                    is_exit = true;
                    break;
                }
            }
        }

        if (is_exit)
            break;

        try
        {
            double number = std::stod(buffer);
            stack.push(number);
        }
        catch (const std::invalid_argument& e)
        {
            console_window.print("Error: Entrada <" + buffer + "> no reconocida como valida.");
        }

        for (size_t i = 0; i < stack.size(); i++)
        {
            console_window.move(i, 2);
            std::stringstream ss;
            ss << i + 1 << ": " << stack[i];
            console_window.print(ss.str());
        }

        line = stack.size();
    }

    endwin();

    return 0;
}
