#ifndef _SYS_CMDS_H_
#define _SYS_CMDS_H_

#include <unistd.h>
void exec_proc(char **ind_cmd_tokens, int no_of_tokens_in_cmd, int bg_flag);

#endif