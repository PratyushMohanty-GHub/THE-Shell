#include "../global.h"
#include "helper.h"

void get_rel_path(char *abs_path, char *rel_path)
{
    if (strlen(abs_path) < strlen(abs_home_dir_path))
    {
        strcpy(rel_path, abs_path);
        return;
    }
    for (int i = 0; i < strlen(abs_home_dir_path); i++)
    {
        if (abs_path[i] != abs_home_dir_path[i])
        {
            strcpy(rel_path, abs_path);
            return;
        }
    }
    int i = strlen(abs_home_dir_path);
    rel_path[0] = '~';
    for (i = strlen(abs_home_dir_path); i < strlen(abs_path); i++)
    {
        rel_path[i + 1 - strlen(abs_home_dir_path)] = abs_path[i];
    }
    rel_path[i + 1 - strlen(abs_home_dir_path)] = '\0';
}
char **create_cmd_matrix()
{
    char **cmd_matrix = (char **)calloc(MAX_STR_LEN, sizeof(char) * MAX_STR_LEN);
    for (int i = 0; i < MAX_STR_LEN; i++)
        cmd_matrix[i] = NULL;

    return cmd_matrix;
}
char get_process_status(pid_t pro_id)
{
    char path1[MAX_PATH_LEN];
    sprintf(path1, "/proc/%d/status", pro_id);
    FILE *f_ptr1 = fopen(path1, "r");

    char pro_status;
    char buffer[256];
    if (f_ptr1 != NULL)
    {
        int i = 0;
        while (fgets((buffer), sizeof(buffer), f_ptr1))
        {
            i++;
            if (i == 3)
            {
                sscanf(buffer, "State:\t%c", &pro_status);
                break;
            }
        }
        fclose(f_ptr1);
    }
    else
    {
        // perror("Not able to open proc/pid/status file");
        pro_id = '\0';

        // int act_status = INVALID;
        // for (int i = 0; i < no_of_jobs; i++)
        // {
        //     if (job_detail[i].id == pro_id)
        //         act_status = job_detail[i].isActive;
        // }
        // // perror("Not able to open proc/pid/status file");
        // if (act_status == false)
        //     pro_status = 'T';
        // else
        //     pro_status = '\0';
    }
    return pro_status;
}