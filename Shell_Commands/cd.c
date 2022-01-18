#include "../global.h"
#include "cd.h"

void _cd(char **ind_cmd_tokens, int no_of_ind_cmds)
{
    if (no_of_ind_cmds == 1 || (no_of_ind_cmds == 2 && strcmp(ind_cmd_tokens[1], "~") == 0))
    {
        getcwd(abs_prev_dir_path, MAX_PATH_LEN);
        if (chdir(abs_home_dir_path) < 0)
        {
            perror("No such file or directory");
            return;
        }
    }
    else if (no_of_ind_cmds == 2)
    {
        if (strcmp(ind_cmd_tokens[1], "-") == 0)
        {
            char *temp_prev_path = (char *)calloc(MAX_PATH_LEN, sizeof(char));
            strcpy(temp_prev_path, abs_prev_dir_path);

            getcwd(abs_prev_dir_path, MAX_PATH_LEN);
            if (chdir(temp_prev_path) < 0)
            {
                perror("No such file or directory");
                return;
            }
            free(temp_prev_path);
        }
        else
        {
            getcwd(abs_prev_dir_path, MAX_PATH_LEN);
            if (strlen(ind_cmd_tokens[1]) >= 2 && ind_cmd_tokens[1][0] == '~' && ind_cmd_tokens[1][1] == '/')
            {
                if (chdir(abs_home_dir_path) < 0)
                {
                    perror("No such file or directory");
                    return;
                }
                if (chdir(ind_cmd_tokens[1] + 1) < 0)
                {
                    perror("No such file or directory");
                    return;
                }
            }
            else
            {
                if (chdir(ind_cmd_tokens[1]) < 0)
                {
                    perror("No such file or directory");
                    return;
                }
            }
        }
    }
    else
    {
        perror("Incorrect number of arguments");
        // exit(1);
    }
}