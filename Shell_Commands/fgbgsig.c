#include "../global.h"
#include "fgbgsig.h"

void _fg(char **ind_cmd_tokens, int no_of_tokens_in_cmd)
{
    if (no_of_tokens_in_cmd != 2)
    {
        perror("Incorrect no. of arguments");
        return;
    }
    else
    {
        int job_no = atoi(ind_cmd_tokens[1]);
        if (job_no > total_no_of_jobs || job_no < 1)
        {
            perror("No background job corresponding to the given job number exists");
            return;
        }
        else
        {
            proc given_job;
            int job_found = false;
            for (int i = 0; i < curr_no_of_jobs; i++)
            {
                if (job_no == job_detail[i].job_no)
                {
                    job_found = true;
                    given_job = job_detail[i];
                    break;
                }
            }
            if (job_found == false)
            {
                perror("No background job corresponding to the given job number exists");
                return;
            }
            else
            {
                // When SIGSTOP is sent to a process, the usual behaviour is to pause that process in its current state.
                // The process will only resume execution if it is sent the SIGCONT signal.
                // In short, SIGSTOP tells a process to “hold on” and SIGCONT tells a process to “pick up where you left off”.

                int job_id = given_job.id;
                // printf("%d %d\n", curr_no_of_jobs, total_no_of_jobs);

                add_job_to_fg_joblist(given_job);
                // printf("%d %d\n", curr_no_of_jobs, total_no_of_jobs);

                delete_process_from_jl(given_job);
                // printf("%d %d\n", curr_no_of_jobs, total_no_of_jobs);

                kill(given_job.id, SIGCONT);
                // printf("%d %d\n", curr_no_of_jobs, total_no_of_jobs);

                int status;
                waitpid(given_job.id, &status, WUNTRACED);

                // The shell can continue a stopped job by sending a SIGCONT signal to its process group.
                // If the job is being continued in the foreground, the shell should first invoke tcsetpgrp to give the job access to the terminal, and restore the saved terminal settings.

                // printf("Test1\n");
                // printf("Test2\n");
                // printf("%d %d\n", curr_no_of_jobs, total_no_of_jobs);
            }
        }
        update_job_status();
    }
}
void _bg(char **ind_cmd_tokens, int no_of_tokens_in_cmd)
{
    if (no_of_tokens_in_cmd != 2)
    {
        perror("Incorrect no. of arguments");
        return;
    }
    else
    {
        int job_no = atoi(ind_cmd_tokens[1]);
        if (job_no > total_no_of_jobs || job_no < 1)
        {
            perror("No background job corresponding to the given job number exists");
            return;
        }
        else
        {
            proc given_job;
            int job_found = false;
            for (int i = 0; i < curr_no_of_jobs; i++)
            {
                if (job_no == job_detail[i].job_no)
                {
                    job_found = true;
                    given_job = job_detail[i];
                    break;
                }
            }
            if (job_found == false)
            {
                perror("No background job corresponding to the given job number exists");
                return;
            }
            else
            {
                // printf("%d %d\n", given_job.id, given_job.isActive);
                if (given_job.isActive == true)
                {
                    printf("Job is already running in the background\n");
                    return;
                }
                else
                {
                    // When SIGSTOP is sent to a process, the usual behaviour is to pause that process in its current state.
                    // The process will only resume execution if it is sent the SIGCONT signal.
                    // In short, SIGSTOP tells a process to “hold on” and SIGCONT tells a process to “pick up where you left off”.

                    kill(given_job.id, SIGCONT);
                    job_detail[job_no - 1].isActive = true;
                }
            }
        }
        update_job_status();
    }
}
void _sig(char **ind_cmd_tokens, int no_of_tokens_in_cmd)
{
    if (no_of_tokens_in_cmd != 3)
    {
        perror("Incorrect no. of arguments");
        return;
    }
    else
    {
        int job_no = atoi(ind_cmd_tokens[1]);
        int sig_no = atoi(ind_cmd_tokens[2]);
        if (job_no > total_no_of_jobs || job_no < 1)
        {
            perror("No background job corresponding to the given job number exists");
            return;
        }
        else
        {
            proc given_job;
            int job_found = false;
            for (int i = 0; i < curr_no_of_jobs; i++)
            {
                if (job_no == job_detail[i].job_no)
                {
                    job_found = true;
                    given_job = job_detail[i];
                    break;
                }
            }
            if (job_found == false)
            {
                perror("No background job corresponding to the given job number exists");
                return;
            }
            else
            {
                if (given_job.isActive == false)
                {
                    printf("Job is not running in the background\n");
                    return;
                }
                else
                {
                    if (kill(given_job.id, sig_no) < 0)
                    {
                        perror("Wrong signal number");
                    }
                    for (int i = 0; i < curr_no_of_jobs; i++)
                    {
                        char proc_status = get_process_status(job_detail[i].id);
                        if (proc_status == '\0')
                        {
                            delete_process_from_jl(given_job);
                        }
                    }
                }
            }
        }
        update_job_status();
    }
}