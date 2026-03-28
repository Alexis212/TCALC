#include <exception>
#include <string>
#include <vector>
#include <iostream>
#include <cctype>
#include "helpers.hpp"

using std::cout;
using std::cin;


int main(int argc, char *argv[])
{
    bool is_quit = false;
    bool is_dot_in_buffer = false;

    char char_buffer;
    std::string buffer;
    std::vector<double> stack;

    enableRawMode();

    while (true)
    {
        buffer = "";
        cout << " > ";

        while (cin.get(char_buffer))
        {
            // Behavior of BACKSPACE
            if (char_buffer == '\x7f')
            {
                if (!buffer.empty())
                {
                    if (buffer.back() == '.')
                        is_dot_in_buffer = false;

                    buffer.pop_back();
                    cout << "\b \b";
                }

                continue;
            }

            else if (char_buffer == 'q')
            {
                is_quit = true;
                cout << "\n";
                break;
            }

            // Send data with RET or SPACE
            else if (char_buffer == '\n' or char_buffer == ' ')
            {
                cout << "\n";
                break;
            }

            // Only send '.' or a digit to buffer
            else if (char_buffer == '.' and not is_dot_in_buffer)
            {
                cout << char_buffer;
                buffer.push_back(char_buffer);
                is_dot_in_buffer = true;
            }

            else if (std::isdigit(char_buffer))
            {
                cout << char_buffer;
                buffer.push_back(char_buffer);
            }
        }

        if (is_quit)
            break;

        is_dot_in_buffer = false;

        try
        {
            stack.push_back(std::stod(buffer));

            if (buffer.empty())
                cout << "." << "\n";

            else
                cout << stack.back() << "\n";
        }

        catch (std::exception &e)
        {
            cout << "FIXME: Buffer read more than it need" << "\n";
        }
    }

    disableRawMode();
    return 0;
}
