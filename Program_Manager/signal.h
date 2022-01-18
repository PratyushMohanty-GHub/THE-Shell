#ifndef _SIGNAL_H_
#define _SIGNAL_H_

void signal_handler();
void init_exit_signal();

void handle_ctrlC();
void handle_ctrlZ();
void handle_ctrlD();

void handle_other_signals();

#endif