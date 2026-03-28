#include "helpers.hpp"

struct termios old_term;

void enableRawMode()
{
    // Obtenemos configuración actual
    tcgetattr(STDIN_FILENO, &old_term);
    struct termios new_term = old_term;

    /*
     * Desactivamos las flags:
     * ECHO: Se imprimen los caracteres
     * ICANON: Espera al enter para enviar
     * IEXTEN: Procesamiento de caracteres extendidos (???)
     * ISIG: Las señales espaciales (Ctrl+C, Ctrl+D, Ctrl+Z)
     */
    new_term.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &new_term);
}

void disableRawMode()
{
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &old_term);
}

double binary_operators(char oper, double a, double b)
{
    switch (oper)
    {
        case '+':
            return b + a;
        case '-':
            return b - a;
        case '*':
            return b * a;
        case '/':
            return b / a;
    }

    return 0;
}
