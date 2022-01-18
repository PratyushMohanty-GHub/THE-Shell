#include "../global.h"
#include "signal.h"

void signal_handler()
{
    int proc_status;
    pid_t proc_id = waitpid(-1, &proc_status, WNOHANG);

    if (proc_id < 0)
        return;

    int i = 0;
    char proc_name[100];
    for (i = 0; i < curr_no_of_jobs; i++)
    {
        if (job_detail[i].id == proc_id && job_detail[i].isActive == true)
        {
            strcpy(proc_name, job_detail[i].proc_name);
            break;
        }
        else if (job_detail[i].id == proc_id && job_detail[i].isActive == false)
        {
            printf("\n%s with pid %d is Inactive\n", proc_name, proc_id);
            return;
        }
    }
    if (i == curr_no_of_jobs)
        return;

    if (proc_id < 0)
        return;
    if (WIFEXITED(proc_status) && WEXITSTATUS(proc_status) == EXIT_SUCCESS)
    {
        print_in_white;
        printf("\n%s with pid %d exited normally\n", proc_name, proc_id);
        print_in_cyan;
    }
    else
    {
        print_in_white;
        printf("\n%s with pid %d exited abnormally\n", proc_name, proc_id);
        print_in_cyan;

        // exit(1);
    }

    // deactivate_job_from_joblist(proc_id);
    proc bg_proc;
    bg_proc.id = proc_id;
    delete_process_from_jl(bg_proc);
    update_job_status();

    print_shell_prompt();
}
void init_exit_signal()
{
    // SIGCHLD :
    // This signal is sent to a parent process whenever one of its child processes terminates or stops.
    signal(SIGCHLD, signal_handler);
}
void handle_ctrlD()
{
    printf("Logging you out of your shell...\n");
    print_exit_line();
    exit(0);
}
void handle_ctrlC()
{
    if (curr_no_of_jobs <= 0)
        total_no_of_jobs = 0;

    if (is_fg_proc_running == false)
    {
        // perror("No foreground process exists");
        return;
    }
    else
    {
        // printf("Interrupting currently running foreground job\n");
        kill(fg_job_detail[0].id, SIGINT);
        is_fg_proc_running = false;
        printf("\n");
    }
}
void handle_ctrlZ()
{
    if (curr_no_of_jobs <= 0)
        total_no_of_jobs = 0;

    if (is_fg_proc_running == false)
    {
        // perror("No foreground process exists");
        return;
    }
    else
    {
        proc given_job = fg_job_detail[0];
        kill(given_job.id, SIGTSTP);
        printf("\n");
        // printf("Test1\n");
        add_new_job_to_joblist(given_job.id, given_job.proc_name);
        update_job_status();
        // // printf("Test2\n");
        deactivate_job_from_joblist(given_job.id);
        // // printf("Test3\n");
        delete_process_from_fg_jl(given_job);
        // printf("Test4\n");
    }
}
void handle_other_signals()
{
    signal(SIGINT, handle_ctrlC);
    signal(SIGTSTP, handle_ctrlZ);
}

// int SIGSTOP : The SIGSTOP signal stops the process. It cannot be handled, ignored, or blocked.

// int SIGTTIN : A process cannot read from the user’s terminal while it is running as a background job. When any process in a background job tries to read from the terminal, all of the processes in the job are sent a SIGTTIN signal.

// int SIGTTOU : This is similar to SIGTTIN, but is generated when a process in a background job attempts to write to the terminal or set its modes.

// Passing SIG_IGN as handler ignores a given signal (except the signals SIGKILL and SIGSTOP which can't caught or ignored).
