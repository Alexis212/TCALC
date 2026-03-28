#include <string>
#include <iostream>
#include <cctype>
#include "helpers.hpp"


int main(int argc, char *argv[])
{
    std::string buffer;
    char char_buffer;
    enableRawMode();

    while (true)
    {
        buffer = "";
        std::cout << " > ";

        while (std::cin.get(char_buffer))
        {
            if (char_buffer == '\x7f')
            {
                if (!buffer.empty())
                {
                    buffer.pop_back();
                    std::cout << "\b \b";
                }

                continue;
            }

            if (char_buffer == '\n' || char_buffer == ' ')
            {
                std::cout << "\n";
                break;
            }

            if (std::isprint(char_buffer))
            {
                std::cout << char_buffer;
                buffer.push_back(char_buffer);
            }
        }

        std::cout << buffer << "\n";

        if (buffer == "exit")
            break;
    }

    disableRawMode();
    return 0;
}
