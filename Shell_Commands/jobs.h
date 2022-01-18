#ifndef _JOBS_H_
#define _JOBS_H_

#define MAX_NO_OF_JOBS 500

typedef struct
{
    int job_no;
    int isActive;
    
    pid_t id;
    char proc_name[1000];
} proc;

proc curr_proc;

int curr_no_of_jobs;
int total_no_of_jobs;
proc *job_detail;

proc *fg_job_detail;
int is_fg_proc_running;

void init_job_list();
void init_fg_job_list();

void _jobs(int flag_r, int flag_s);

void update_job_status();

void deactivate_job_from_joblist(int proc_id);
void delete_process_from_jl(proc fg_process);
void delete_process_from_fg_jl(proc fg_process);

void add_job_to_fg_joblist(proc fg_process);
void add_new_job_to_joblist(int new_proc_id, char *new_proc_name);

void _jobs_helper(char **ind_cmd_tokens, int no_of_tokens_in_cmd);

#endif