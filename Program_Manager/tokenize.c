#include "../global.h"
#include "tokenize.h"

int separate_cmdline_input(char *input_str, char **ind_cmd)
{
    char *token = strtok(input_str, ";");

    int i = 0;
    while (token != NULL)
    {
        ind_cmd[i++] = token;
        token = strtok(NULL, ";");
    }
    ind_cmd[i] = NULL;

    return i;
}
int account_space_and_tab(char *input_str, char **ind_cmd_tokens)
{
    char *token = strtok(input_str, " \t");

    int i = 0;
    while (token != NULL)
    {
        ind_cmd_tokens[i++] = token;
        token = strtok(NULL, " \t");
    }
    ind_cmd_tokens[i] = NULL;

    int no_of_tokes_in_cmd = i;
    return no_of_tokes_in_cmd;
}
int account_delims(char *input_str, char **ind_cmd_tokens, char *delims)
{
    char *token = strtok(input_str, delims);

    int i = 0;
    while (token != NULL)
    {
        ind_cmd_tokens[i++] = token;
        token = strtok(NULL, delims);
    }
    ind_cmd_tokens[i] = NULL;

    int no_of_tokes_in_cmd = i;
    return no_of_tokes_in_cmd;
}