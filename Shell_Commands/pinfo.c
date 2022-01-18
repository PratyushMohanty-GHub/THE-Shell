#include "../global.h"
#include "pinfo.h"

void _pinfo(char *info_cmd, int no_of_arg)
{
    pid_t pro_id;
    if (no_of_arg == 1)
    {
        pro_id = getpid();
    }
    else if (no_of_arg == 2)
    {
        pro_id = atoi(info_cmd);
    }

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
        perror("Not able to open proc/pid/status file");
        // exit(1);
    }
    // Process Status

    char pathx[MAX_PATH_LEN];
    sprintf(pathx, "/proc/%d/stat", pro_id);
    FILE *f_ptrx = fopen(pathx, "r");

    char status_sym = '\0';
    char pgrp[10];
    char tpgid[10];
    char word[100];

    if (f_ptrx != NULL)
    {
        int i = 1;
        while (fscanf(f_ptrx, "%s", word) != EOF)
        {
            if (i == 5)
            {
                strcpy(pgrp, word);
            }
            if (i == 8)
            {
                strcpy(tpgid, word);
            }
            if (i > 8)
                break;
            ++i;
        }
        if (strcmp(pgrp, tpgid) == 0)
            status_sym = '+';
        else
            status_sym = ' ';
        fclose(f_ptrx);
    }
    else
    {
        perror("Not able to open proc/pid/stat file");
        // exit(1);
    }

    // memory

    char path2[MAX_PATH_LEN];
    sprintf(path2, "/proc/%d/statm", pro_id);
    FILE *f_ptr2 = fopen(path2, "r");

    int pro_memory;
    if (f_ptr2 != NULL)
    {
        char char_read;
        char pro_mem_str[MAX_STR_LEN];

        int str_len = 0;
        char_read = fgetc(f_ptr2);
        while (char_read != ' ')
        {
            pro_mem_str[str_len++] = char_read;
            char_read = fgetc(f_ptr2);
        }
        pro_mem_str[str_len] = '\0';

        pro_memory = atoi(pro_mem_str);
        fclose(f_ptr2);
    }
    else
    {
        perror("Not able to open proc/pid/statm file");
        // exit(1);
    }

    // Executable Path

    char path3[MAX_PATH_LEN];
    char pro_exe_path[MAX_PATH_LEN];
    sprintf(path3, "/proc/%d/exe", pro_id);

    int path_len = readlink(path3, pro_exe_path, MAX_PATH_LEN - 1);
    pro_exe_path[path_len] = '\0';

    if (path_len == -1)
    {
        perror("Not able to open proc/pid/exe file");
        // exit(1);
    }

    char *rel_exe_path = (char *)calloc(MAX_PATH_LEN, sizeof(char));
    get_rel_path(pro_exe_path, rel_exe_path);
    printf("pid -- %d\n", pro_id);
    if (f_ptr1 != NULL)
        printf("Process Status -- %c%c\n", pro_status, status_sym);
    if (f_ptr2 != NULL)
        printf("memory -- %d {Virtual Memory}\n", pro_memory);
    if (path_len != -1)
        printf("Executable Path -- %s\n", rel_exe_path);
    free(rel_exe_path);
}