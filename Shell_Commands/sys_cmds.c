#include "../global.h"
#include "sys_cmds.h"

void exec_proc(char **ind_cmd_tokens, int no_of_tokens_in_cmd, int bg_flag)
{
    if (bg_flag == 0) // Foreground Process
    {
        int proc_status;
        pid_t proc_id = fork();

        if (proc_id < 0)
        {
            perror("Error in fork");
            exit(EXIT_FAILURE);
        }
        else if (proc_id == 0)
        {
            // Child Process
            signal(SIGINT, SIG_DFL);
            signal(SIGTSTP, SIG_DFL);
            signal(SIGCHLD, SIG_DFL);
            setpgid(0, 0);

            if (execvp(ind_cmd_tokens[0], ind_cmd_tokens) < 0)
                perror("Error in execvp");
        }
        else
        {
            // Parent Process
            dup2(STD_INP_DUP, STDIN_FILENO);
            dup2(STD_OUT_DUP, STDOUT_FILENO);

            proc fg_proc;
            fg_proc.job_no = 1;
            fg_proc.id = proc_id;
            fg_proc.isActive = true;
            strcpy(fg_proc.proc_name, ind_cmd_tokens[0]);

            add_job_to_fg_joblist(fg_proc);

            waitpid(proc_id, &proc_status, WUNTRACED);

            delete_process_from_fg_jl(fg_proc);
        }
    }
    else if (bg_flag == 1) // Background Process
    {
        int proc_status;
        pid_t proc_id = fork();

        if (proc_id < 0)
        {
            perror("Error in fork");
            exit(EXIT_FAILURE);
        }
        else if (proc_id == 0)
        {
            // Child Process
            signal(SIGINT, SIG_DFL);
            signal(SIGTSTP, SIG_DFL);
            signal(SIGCHLD, SIG_DFL);
            setpgid(0, 0);

            if (execvp(ind_cmd_tokens[0], ind_cmd_tokens) < 0)
            {
                perror("Error in execvp");
                exit(1);
            }
        }
        else
        {
            // Parent Process
            printf("[%d] %s\n", proc_id, ind_cmd_tokens[0]);

            dup2(STD_INP_DUP, STDIN_FILENO);
            dup2(STD_OUT_DUP, STDOUT_FILENO);

            add_new_job_to_joblist(proc_id, ind_cmd_tokens[0]);
        }
    }
    else
        perror("Wrong flag");
}