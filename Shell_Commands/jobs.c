#include "../global.h"
#include "jobs.h"

void init_job_list()
{
    curr_no_of_jobs = 0;
    total_no_of_jobs = 0;
    job_detail = (proc *)calloc(MAX_NO_OF_JOBS, sizeof(proc));
}
void init_fg_job_list()
{
    is_fg_proc_running = false;
    fg_job_detail = (proc *)calloc(1, sizeof(proc));
}
void add_new_job_to_joblist(int new_proc_id, char *new_proc_name)
{
    if (curr_no_of_jobs <= 0)
        total_no_of_jobs = 0;
    if (curr_no_of_jobs + 1 > MAX_NO_OF_JOBS)
        return;

    curr_no_of_jobs++;
    total_no_of_jobs++;
    job_detail[curr_no_of_jobs - 1].job_no = total_no_of_jobs;
    job_detail[curr_no_of_jobs - 1].id = new_proc_id;
    job_detail[curr_no_of_jobs - 1].isActive = true;
    strcpy(job_detail[curr_no_of_jobs - 1].proc_name, new_proc_name);
}
void update_job_status()
{
    for (int i = 0; i < curr_no_of_jobs; i++)
    {
        char proc_status = get_process_status(job_detail[i].id);
        if (proc_status != '\0')
        {
            if (proc_status == 'T' || proc_status == 't')
                job_detail[i].isActive = false;
            if (proc_status == 'R' || proc_status == 'S')
                job_detail[i].isActive = true;
            // printf("%c %d %d", proc_status, job_detail[i].id, job_detail[i].isActive);
        }
    }
}
void add_job_to_fg_joblist(proc fg_process)
{
    fg_job_detail[0].job_no = 1;
    fg_job_detail[0].id = fg_process.id;
    fg_job_detail[0].isActive = true;
    strcpy(fg_job_detail[0].proc_name, fg_process.proc_name);
    is_fg_proc_running = true;
}
void deactivate_job_from_joblist(int proc_id)
{
    for (int i = 0; i < curr_no_of_jobs; i++)
    {
        if (job_detail[i].id == proc_id)
        {
            job_detail[i].isActive = false;
            break;
        }
    }
}
void delete_process_from_fg_jl(proc fg_process)
{
    if (is_fg_proc_running == false)
        return;

    is_fg_proc_running = false;
}
void delete_process_from_jl(proc bg_process)
{
    if (curr_no_of_jobs <= 0)
        total_no_of_jobs = 0;
    
    int mark_idx = -1;
    for (int i = 0; i < curr_no_of_jobs; i++)
    {
        if (bg_process.id == job_detail[i].id)
        {
            mark_idx = i;
            break;
        }
    }
    if (mark_idx < 0 || mark_idx >= curr_no_of_jobs)
    {
        perror("Job not found");
        return;
    }

    for (int i = mark_idx; i < curr_no_of_jobs - 1; i++)
    {
        job_detail[i] = job_detail[i + 1];
    }
    curr_no_of_jobs--;
}
void _jobs_helper(char **ind_cmd_tokens, int no_of_tokens_in_cmd)
{
    int flag_r = false, flag_s = false;
    for (int i = 1; i < no_of_tokens_in_cmd; i++)
    {
        if (strcmp(ind_cmd_tokens[i], "-r") == 0 ||
            strcmp(ind_cmd_tokens[i], "-sr") == 0 ||
            strcmp(ind_cmd_tokens[i], "-rs") == 0)
            flag_r = true;
        if (strcmp(ind_cmd_tokens[i], "-s") == 0 ||
            strcmp(ind_cmd_tokens[i], "-sr") == 0 ||
            strcmp(ind_cmd_tokens[i], "-rs") == 0)
            flag_s = true;
    }
    if (no_of_tokens_in_cmd == 1)
    {
        flag_r = true;
        flag_s = true;
    }

    _jobs(flag_r, flag_s);
}
void _jobs(int flag_r, int flag_s)
{
    proc jobs_list_copy[curr_no_of_jobs];
    for (int i = 0; i < curr_no_of_jobs; i++)
    {
        jobs_list_copy[i] = job_detail[i];
    }

    sort_struct_array(jobs_list_copy, curr_no_of_jobs);

    for (int i = 0; i < curr_no_of_jobs; i++)
    {
        char proc_status = get_process_status(jobs_list_copy[i].id);
        if (proc_status != '\0')
        {
            char print_status[20] = "\0";
            if (flag_r == true && (proc_status == 'R' || proc_status == 'S'))
            {
                strcpy(print_status, "Running");
                printf("[%d] %s %s [%d]\n", jobs_list_copy[i].job_no, print_status, jobs_list_copy[i].proc_name, jobs_list_copy[i].id);
            }
            else if (flag_s == true && (proc_status == 'T' || proc_status == 't'))
            {
                strcpy(print_status, "Stopped");
                printf("[%d] %s %s [%d]\n", jobs_list_copy[i].job_no, print_status, jobs_list_copy[i].proc_name, jobs_list_copy[i].id);
            }
            // else if (proc_status == 'D' || proc_status == 'S')
            // {
            //     strcpy(print_status, "Sleeping");
            //     printf("[%d] %s %s [%d]\n", i + 1, print_status, jobs_list_copy[i].proc_name, jobs_list_copy[i].id);
            // }
        }
    }
}