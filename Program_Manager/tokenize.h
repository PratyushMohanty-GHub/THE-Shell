#ifndef _TOKENIZE_H_
#define _TOKENIZE_H_

int separate_cmdline_input(char *input_str, char **ind_cmd);
int account_space_and_tab(char *input_str, char **ind_cmd_tokens);
int account_delims(char *input_str, char **ind_cmd_tokens, char *delims);

#endif