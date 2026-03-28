#ifndef HELPERS_H_
#define HELPERS_H_

#include <termios.h>
#include <unistd.h>

extern struct termios old_term;

void enableRawMode();
void disableRawMode();

double binary_operators(char, double, double);

#endif // HELPERS_H_
