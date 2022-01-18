#include "../global.h"
#include "fetch.h"

void check_RDNP_and_execute_cmd(char *command)
{
    check_for_piping(command);

    // Restore STDIN_FILENO
    dup2(STD_INP_DUP, STDIN_FILENO);
    // Restore STDOUT_FILENO 
    dup2(STD_OUT_DUP, STDOUT_FILENO);
}
void fetch_and_execute_next_ins()
{
    char **ind_cmd = create_cmd_matrix();

    char *input = read_cmdline_input();

    // UPDATING THE HISTORY
    update_history(input);
    if (input != NULL)
    {
        last_seen_idx = 20;

        int no_of_cmds = separate_cmdline_input(input, ind_cmd);

        for (int i = 0; i < no_of_cmds; i++)
        {
            // Check for I/O redirection and Piping for each command
            check_RDNP_and_execute_cmd(ind_cmd[i]);
        }
    }
    free(input);
    free(ind_cmd);
}