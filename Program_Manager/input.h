#ifndef _INPUT_H_
#define _INPUT_H_

#include <ctype.h>
#include <termios.h>

struct termios orig_termios;

void die(const char *s);
void disableRawMode();
void enableRawMode();
char *read_cmdline_input();
char get_input();

#endif