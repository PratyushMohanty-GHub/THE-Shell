#include "../global.h"
#include "io_redirection.h"

int *check_for_redirection(char **tokens_of_token, int *final_no_of_tokens_of_token)
{
    int *redir_fdes = (int *)malloc(2 * sizeof(int));
    // printf("redir_fdes[1] %d\n", redir_fdes[1]);
    redir_fdes[0] = -1, redir_fdes[1] = -1;

    char *input_filename = (char *)calloc(MAX_STR_LEN, sizeof(char));
    char *output_filename = (char *)calloc(MAX_STR_LEN, sizeof(char));

    int no_of_tokens_of_token = *final_no_of_tokens_of_token;

    int toAppend = false;
    int ins_idx = INVALID, ext_idx = INVALID;
    // printf("Test30\n");
    for (int i = 0; i < no_of_tokens_of_token; i++)
    {
        int nextIdx = i + 1;
        // printf("Test31\n");

        if (strcmp(tokens_of_token[i], "<") == 0)
        {
            if (tokens_of_token[nextIdx] != NULL)
            {
                {
                    strcpy(input_filename, tokens_of_token[nextIdx]);
                    // printf("%s\n", tokens_of_token[nextIdx]);
                    ins_idx = i;
                }
            }
            else
            {
                redir_fdes[0] = INVALID;
                // set STDOUT_FILENO to STD_OUT_DUP to print ERROR
                dup2(STD_OUT_DUP, STDOUT_FILENO);

                printf("Error in syntax\n");
                return redir_fdes;
            }
        }
        else if (strcmp(tokens_of_token[i], ">") == 0)
        {
            // printf("Test32\n");
            // To print the output in output_file in APPEND mode
            toAppend = false;
            if (tokens_of_token[nextIdx] != NULL)
            {
                // printf("Test321\n");
                ext_idx = i;
                // printf("Test322\n");
                strcpy(output_filename, tokens_of_token[nextIdx]);
                // printf("Test323\n");
            }
            else
            {
                redir_fdes[1] = INVALID;
                // set STDOUT_FILENO to STD_OUT_DUP to print ERROR
                dup2(STD_OUT_DUP, STDOUT_FILENO);

                printf("Error in syntax\n");
                return redir_fdes;
            }
        }
        else if (strcmp(tokens_of_token[i], ">>") == 0)
        {
            // printf("Test33\n");
            // To print the output in output_file in APPEND mode
            toAppend = true;
            if (tokens_of_token[nextIdx] != NULL)
            {
                ext_idx = i;
                strcpy(output_filename, tokens_of_token[nextIdx]);
            }
            else
            {
                redir_fdes[1] = INVALID;
                // set STDOUT_FILENO to STD_OUT_DUP to print ERROR
                dup2(STD_OUT_DUP, STDOUT_FILENO);

                printf("Error in syntax\n");
                return redir_fdes;
            }
        }
    }
    // printf("Test37\n");

    if (ins_idx == INVALID)
    {
        // NO INPUT redirection
        // To use the piped INPUT fdes
        // printf("No Input redir\n");
    }
    else
    {
        // Remove the '<' and the input_filename from the command
        for (int i = ins_idx; i < no_of_tokens_of_token - 2; i++)
        {
            strcpy(tokens_of_token[i], tokens_of_token[i + 2]);
        }
        tokens_of_token[no_of_tokens_of_token - 2] = NULL;
        tokens_of_token[no_of_tokens_of_token - 1] = NULL;
        no_of_tokens_of_token -= 2;

        // Open the input file and store its file desc in redir_fdes[0].
        redir_fdes[0] = open(input_filename, O_RDONLY, S_IRWXU);
        if (redir_fdes[0] < 0)
        {
            redir_fdes[0] = INVALID;
            perror("Error in opening file");
        }
    }
    // printf("Test38\n");

    if (ext_idx == INVALID)
    {
        // NO OUTPUT redirection
        // To use the piped OUTPUT fdes
        // printf("No Output redir\n");
    }
    else
    {
        // Remove the '>' or '>>' and the output_filename from the command
        for (int i = ext_idx; i < no_of_tokens_of_token - 2; i++)
        {
            strcpy(tokens_of_token[i], tokens_of_token[i + 2]);
        }
        tokens_of_token[no_of_tokens_of_token - 2] = NULL;
        tokens_of_token[no_of_tokens_of_token - 1] = NULL;
        no_of_tokens_of_token -= 2;

        if (toAppend == true)
        {
            // Open the output file in APPEND mode and store its file desc in redir_fdes[1].
            redir_fdes[1] = open(output_filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
            if (redir_fdes[1] < 0)
            {
                redir_fdes[1] = INVALID;
                perror("Error in opening file");
            }
        }
        else
        {
            // CREATE the output file  and store its file desc in redir_fdes[1].
            redir_fdes[1] = open(output_filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
            if (redir_fdes[1] < 0)
            {
                redir_fdes[1] = INVALID;
                perror("Error in opening file");
            }
        }
    }
    // printf("Test39\n");
    // printf("redir_fdes[1] %d\n", redir_fdes[1]);
    free(input_filename);
    free(output_filename);

    // Update the no_of_tokens in cmd
    *final_no_of_tokens_of_token = no_of_tokens_of_token;
    return redir_fdes;
}