#include "../global.h"
#include "piping.h"

void check_for_piping(char *command)
{
    // Count the no. of '|' in the command
    int no_of_pipes = 0;
    for (int i = 0; i < strlen(command); i++)
    {
        if (command[i] == '|')
            ++no_of_pipes;
    }

    // Tokenize the command on th basis of '|'
    char **ind_piped_tokens = create_cmd_matrix();
    int no_of_tokens = account_delims(command, ind_piped_tokens, "|");

    // If the command has correct syntax:
    if (no_of_pipes == no_of_tokens - 1)
    {
        // Execpt fot the last cmd:
        for (int i = 0; i < no_of_pipes; i++)
        {
            // The array piped_fdes[2] is used to return two file descriptors referring to the ends  of  the  pipe.
            int piped_fdes[2];
            // pipe()  creates  a  pipe,  a unidirectional data channel that can be used for interprocess communication.
            if (pipe(piped_fdes) < 0)
            {
                perror("Error in creating a pipe");
                break;
            }

            // To store the output of the cmd in a temp file, created by pipe()
            // dup2(piped_fdes[1], STDOUT_FILENO)
            if (dup2(piped_fdes[1], STDOUT_FILENO) < 0)
            {
                perror("Error in dup2()");
            }

            // To check for I/O redirection after this and modify the I/O if needed
            execute_piped_cmd(ind_piped_tokens[i]);

            // To take the input of the cmd from the temp file, created by pipe()
            // The input is the output of the command on the left
            // dup2(piped_fdes[0], STDIN_FILENO)
            if (dup2(piped_fdes[0], STDIN_FILENO) < 0)
            {
                perror("Error in dup2()");
            }
            close(piped_fdes[1]);
        }

        // For the LAST Piped cmd or the ONLY cmd without any pipes, the def output is STD_OUT_DUP.
        dup2(STD_OUT_DUP, STDOUT_FILENO);
        execute_piped_cmd(ind_piped_tokens[no_of_pipes]);
    }
    // If the command has incorrect syntax:
    else
    {
        perror("Error in command");
        free(ind_piped_tokens);
        return;
    }
    free(ind_piped_tokens);
}
void execute_piped_cmd(char *ind_piped_token)
{
    // printf("Test1\n");
    char **tokens_of_token = create_cmd_matrix();
    int no_of_tokens_of_token = account_space_and_tab(ind_piped_token, tokens_of_token);
    // printf("Test2\n");

    // Check for I/O redirection and modify the I/O if needed
    int *redir_fdes = check_for_redirection(tokens_of_token, &no_of_tokens_of_token);
    // printf("Test3\n");

    if (redir_fdes[0] != INVALID && redir_fdes[1] != INVALID)
    {
        if (redir_fdes[0] >= 0)
        {
            dup2(redir_fdes[0], STDIN_FILENO);
            // close(redir_fdes[0]);
        }
        // else use the one that was piped

        if (redir_fdes[1] >= 0)
        {
            dup2(redir_fdes[1], STDOUT_FILENO);
            // close(redir_fdes[1]);
        }
        // else use the one that was piped
    }
    else
    {
        perror("Error in I/O redirection");
        return;
    }

    execute_cmd(tokens_of_token, no_of_tokens_of_token);
    // printf("Test4\n");
    free(tokens_of_token);
}