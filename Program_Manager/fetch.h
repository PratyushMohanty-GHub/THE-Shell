#ifndef _FETCH_INP_H_
#define _FETCH_INP_H_

int STD_INP_DUP;
int STD_OUT_DUP;

void fetch_and_execute_next_ins();
void check_RDNP_and_execute_cmd(char *command);

#define INVALID -100

#endif