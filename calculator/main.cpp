#include <string>
#include <iostream>
#include <stdexcept>
#include <cctype>

#include "vector_wrapper.hpp"
#include "helpers.hpp"

using std::cout;


int main(int argc, char *argv[])
{
    bool is_quit = false;
    bool is_dot_in_buffer = false;
    bool is_e_in_buffer = false;

    char char_buffer;
    std::string buffer;
    VectorWrapper stack;

    enableRawMode();

    while (true)
    {
        buffer = "";
        cout << " > ";

        while (std::cin.get(char_buffer))
        {
            // Quit the application
            if (char_buffer == 'q')
            {
                is_quit = true;
                cout << "\n";
                break;
            }

            // Behavior of BACKSPACE
            else if (char_buffer == '\x7f')
            {
                if (!buffer.empty())
                {
                    if (buffer.back() == '.')
                        is_dot_in_buffer = false;

                    if (buffer.back() == 'e')
                        is_e_in_buffer = false;

                    buffer.pop_back();
                    cout << "\b \b";
                    continue;
                }

                stack.remove_top();
                break;
            }

            // Enable negative numbers
            else if (char_buffer == '_' && buffer.empty())
            {
                buffer.push_back('-');
                cout << "-";
            }

            else if (char_buffer == '\t')
            {
                if (buffer.empty())
                    stack.swap_top();

                break;
            }

            // Send data with RET or SPACE
            else if (char_buffer == ' ' && !buffer.empty())
                break;

            else if (char_buffer == '\n')
            {
                if (buffer.empty())
                    stack.duply_top();

                break;
            }

            // Support decimals and e notation
            else if (char_buffer == 'e' && !is_e_in_buffer)
            {
                if (buffer.empty())
                {
                    cout << "1e";
                    buffer.push_back('1');
                    buffer.push_back('e');
                }

                else
                {
                    cout << char_buffer;
                    buffer.push_back(char_buffer);
                }

                is_e_in_buffer = true;
            }

            else if (char_buffer == '.' && !is_dot_in_buffer)
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
        is_e_in_buffer = false;

        // Procesamos el valor del buffer.
        if (buffer == ".")
        {
            stack.print_top();
            continue;
        }

        try
        {
            if (!buffer.empty())
                stack.push(std::stod(buffer));

            stack.print_top();
        }

        catch (std::invalid_argument &e)
        {
            cout << "ERROR <push>: Se intento enviar al stack una entrada invalida.\n";
        }
    }

    disableRawMode();
    return 0;
}
