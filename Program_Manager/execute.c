#include "../global.h"
#include "execute.h"

void print_exit_line()
{
    printf("\n");
    for (int i = 0; i < 43; i++)
        printf(" ");
    print_in_white;
    printf("***** ");
    print_bold_in_red;
    printf("Thank ");
    print_in_cyan;
    printf("You ");

    print_in_green;
    printf("!");
    print_in_white;
    printf("!");
    print_in_red;
    printf("!");
    print_in_white;
    printf(" *****\n");
}
void execute_cmd(char **ind_cmd_tokens, int no_of_tokens_in_cmd)
{
    int bg_flag = 0;
    if (strcmp(ind_cmd_tokens[no_of_tokens_in_cmd - 1], "&") == 0)
    {
        ind_cmd_tokens[no_of_tokens_in_cmd - 1] = NULL;
        --no_of_tokens_in_cmd;
        bg_flag = 1;
    }

    if (strcmp(ind_cmd_tokens[0], "cd") == 0)
    {
        _cd(ind_cmd_tokens, no_of_tokens_in_cmd);
    }
    else if (strcmp(ind_cmd_tokens[0], "baywatch") == 0)
    {
        _baywatch(ind_cmd_tokens, no_of_tokens_in_cmd);
    }
    else if (strcmp(ind_cmd_tokens[0], "echo") == 0)
    {
        _echo(ind_cmd_tokens, no_of_tokens_in_cmd);
    }
    else if (strcmp(ind_cmd_tokens[0], "pwd") == 0)
    {
        char *pwd = _pwd();
        printf("Relative Path: %s\n", pwd);
        free(pwd);
    }
    else if (strcmp(ind_cmd_tokens[0], "jobs") == 0)
    {
        _jobs_helper(ind_cmd_tokens, no_of_tokens_in_cmd);
    }
    else if (strcmp(ind_cmd_tokens[0], "replay") == 0)
    {
        _replay(ind_cmd_tokens, no_of_tokens_in_cmd);
    }
    else if (strcmp(ind_cmd_tokens[0], "ls") == 0)
    {
        _ls(ind_cmd_tokens, no_of_tokens_in_cmd);
    }
    else if (strcmp(ind_cmd_tokens[0], "sig") == 0)
    {
        _sig(ind_cmd_tokens, no_of_tokens_in_cmd);
    }
    else if (strcmp(ind_cmd_tokens[0], "bg") == 0)
    {
        _bg(ind_cmd_tokens, no_of_tokens_in_cmd);
    }
    else if (strcmp(ind_cmd_tokens[0], "fg") == 0)
    {
        _fg(ind_cmd_tokens, no_of_tokens_in_cmd);
    }
    else if (strcmp(ind_cmd_tokens[0], "pinfo") == 0)
    {
        char *pinfo_cmd = NULL;
        if (no_of_tokens_in_cmd == 2)
        {
            pinfo_cmd = (char *)calloc(100, sizeof(char));
            strcpy(pinfo_cmd, ind_cmd_tokens[1]);
        }

        _pinfo(pinfo_cmd, no_of_tokens_in_cmd);
        free(pinfo_cmd);
    }
    else if (strcmp(ind_cmd_tokens[0], "repeat") == 0)
    {
        _repeat(ind_cmd_tokens, no_of_tokens_in_cmd);
    }
    else if (strcmp(ind_cmd_tokens[0], "clear") == 0)
    {
        printf("\033[H\033[J");
    }
    else if (strcmp(ind_cmd_tokens[0], "history") == 0)
    {
        _history(ind_cmd_tokens, no_of_tokens_in_cmd);
    }
    else if (strcmp(ind_cmd_tokens[0], "exit") == 0 || strcmp(ind_cmd_tokens[0], "quit") == 0)
    {
        print_exit_line();
        exit(0);
    }
    else
    {
        // for (int i = 0; i < no_of_tokens_in_cmd; i++)
        //     printf("%s\n", ind_cmd_tokens[i]);
        exec_proc(ind_cmd_tokens, no_of_tokens_in_cmd, bg_flag);
    }
}