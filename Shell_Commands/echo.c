#include "../global.h"
#include "echo.h"

void _echo(char **ind_cmd_tokens, int no_of_ind_cmds)
{
    if (strcmp(ind_cmd_tokens[1], "") == 0)
    {
        printf("\n");
        return;
    }
    else if (ind_cmd_tokens[1][0] == '$')
    {
        char *ENV = (char *)calloc(10, sizeof(char));
        int i = 1;
        while (ind_cmd_tokens[1][i] != '\0')
        {
            ENV[i - 1] = ind_cmd_tokens[1][i];
            i++;
        }
        ENV[i - 1] = ind_cmd_tokens[1][i];
        printf("%s\n", getenv(ENV));
        return;
    }
    else
    {
        // printf("*\n");
        for (int i = 1; i < no_of_ind_cmds; i++)
            printf("%s ", ind_cmd_tokens[i]);
        printf("\n");
    }
}