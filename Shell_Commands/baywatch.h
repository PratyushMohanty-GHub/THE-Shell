#ifndef _BAYWATCH_H_
#define _BAYWATCH_H_

void _baywatch(char **ind_cmd_tokens, int no_of_ind_cmds);

void _baywatch_interrupt(int n);
void _baywatch_newborn(int n);
void _baywatch_dirty(int n);

void _baywatch_dirty_helper();
void _baywatch_newborn_helper();
void _baywatch_interrupt_helper();

int num_H;

#endif