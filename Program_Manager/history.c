#include "../global.h"
#include "history.h"

void _history(char **ind_cmd_tokens, int no_of_tokens_in_cmd)
{
    int display_num_cmds;
    if (no_of_tokens_in_cmd > 2)
    {
        perror("Incorrect number of arguments");
    }
    else
    {
        if (no_of_tokens_in_cmd == 1)
        {
            display_num_cmds = 10;
            // for (int i = 19; i > 9; i--)
            // {
            //     if (strcmp(history_list[i], "_NULL_") != 0)
            //         printf("%s\n", history_list[i]);
            // }
            for (int i = 10; i < 20; i++)
            {
                if (strcmp(history_list[i], "_NULL_") != 0)
                    printf("%s\n", history_list[i]);
            }
        }
        else
        {
            display_num_cmds = atoi(ind_cmd_tokens[1]);
            if (display_num_cmds > 20)
                display_num_cmds = 20;
            // for (int i = 19; i >= 20 - display_num_cmds; i--)
            // {
            //     if (strcmp(history_list[i], "_NULL_") != 0)
            //         printf("%s\n", history_list[i]);
            // }
            for (int i = 20 - display_num_cmds; i < 20; i++)
            {
                if (strcmp(history_list[i], "_NULL_") != 0)
                    printf("%s\n", history_list[i]);
            }
        }
    }
}
void update_history(char *cmd)
{
    // printf("Test1\n");
    if (strcmp(cmd, "") != 0 && strcmp(cmd, history_list[19]) != 0)
    {
        for (int i = 0; i < 19; i++)
        {
            strcpy(history_list[i], history_list[i + 1]);
        }
        strcpy(history_list[19], cmd);
        write_back_history();
    }
}
void read_history()
{
    FILE *hist_file = fopen(abs_history_path, "r");

    size_t len;
    char *cmd = NULL;
    while (getline(&cmd, &len, hist_file) != -1)
    {
        cmd[strlen(cmd) - 1] = '\0';
        strcpy(history_list[no_of_elem_in_history++], cmd);
    }

    fclose(hist_file);
}
void write_back_history()
{
    // printf("test\n");
    FILE *hist_file = fopen(abs_history_path, "w");
    for (int i = 0; i < 20; i++)
        // if (strcmp(history_list[i], "_NULL_") != 0)
        // {
        fprintf(hist_file, "%s\n", history_list[i]);
    // }
    fclose(hist_file);
}