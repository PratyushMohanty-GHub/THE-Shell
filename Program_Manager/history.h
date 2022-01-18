#ifndef _HISTORY_H_
#define _HISTORY_H_

char **history_list;
char *abs_history_path;
int no_of_elem_in_history;
int last_seen_idx;

void _history(char **ind_cmd_tokens, int no_of_tokens_in_cmd);
void update_history(char *cmd);
void read_history();
void write_back_history();

#endif