#include "../global.h"
#include "repeat.h"

void _repeat(char **ind_cmd_tokens, int no_of_ind_cmds)
{
    if (strcmp(ind_cmd_tokens[0], "repeat") == 0 && no_of_ind_cmds >= 3)
    {
        int no_of_times = atoi(ind_cmd_tokens[1]);

        char *argv[no_of_ind_cmds - 1];
        for (int i = 2; i < no_of_ind_cmds; i++)
        {
            argv[i - 2] = ind_cmd_tokens[i];
        }
        argv[no_of_ind_cmds - 2] = NULL;

        for (int i = 0; i < no_of_times; i++)
        {
            pid_t cpid;
            int status = 0;

            cpid = fork();
            if (cpid == 0)
                execvp(ind_cmd_tokens[2], argv);

            wait(&status);

            if (status < 0)
                perror("Abnormal exit of cmd");
        }
    }
    else
        perror("Wrong command");
}
