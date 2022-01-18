#include "../global.h"
#include "baywatch.h"

void _baywatch_interrupt_helper(int first)
{
    FILE *f_ptr = fopen("/proc/interrupts", "r");
    if (f_ptr == NULL)
    {
        perror("Not able to open proc/interruts file");
        return;
    }

    char *input_buffer = (char *)calloc(MAX_STR_LEN, sizeof(char));
    fgets(input_buffer, MAX_STR_LEN, f_ptr);

    if (first == true)
    {
        char **matrix_t = create_cmd_matrix();
        int num_t = account_space_and_tab(input_buffer, matrix_t);
        num_H = num_t;

        // printf(" %s\n", input_buffer);
        for (int i = 0; i < num_t; i++)
            printf(" %s\t", matrix_t[i]);
        printf("\n");
        free(matrix_t);
    }

    fgets(input_buffer, MAX_STR_LEN, f_ptr);
    fgets(input_buffer, MAX_STR_LEN, f_ptr);

    // printf("%s\n", input_buffer + 5);
    char **matrix = create_cmd_matrix();
    int num = account_space_and_tab(input_buffer, matrix);

    for (int i = 1; i < num_H; i++)
        printf(" %s\t", matrix[i]);
    printf("\n");
    
    free(matrix);
    free(input_buffer);

    fflush(stdout);
    fclose(f_ptr);
}
void _baywatch_interrupt(int n)
{
    int num_H = 0;
    int first = true;

    clock_t init_time = clock();
    while (get_input() != 'q')
    {
        clock_t time = (clock() - init_time) / CLOCKS_PER_SEC;
        if (time >= n)
        {
            init_time = clock();
            _baywatch_interrupt_helper(first);
            first = false;
        }
    }
}
void _baywatch_newborn_helper()
{
    FILE *f_ptr = fopen("/proc/loadavg", "r");
    if (f_ptr == NULL)
    {
        perror("Not able to open proc/loadavg file");
        return;
    }

    char *input_buffer = (char *)calloc(MAX_STR_LEN, sizeof(char));
    fgets(input_buffer, 256, f_ptr);

    // printf("%s\n", input_buffer);
    char **matrix = create_cmd_matrix();
    int num = account_space_and_tab(input_buffer, matrix);
    printf(" %s", matrix[num - 1]);
    free(matrix);
    free(input_buffer);

    fflush(stdout);
    fclose(f_ptr);
}
void _baywatch_newborn(int n)
{
    clock_t init_time = clock();
    while (get_input() != 'q')
    {
        clock_t time = (clock() - init_time) / CLOCKS_PER_SEC;
        if (time >= n)
        {
            init_time = clock();
            _baywatch_newborn_helper();
        }
    }
}
void _baywatch_dirty_helper()
{
    FILE *f_ptr = fopen("/proc/meminfo", "r");
    if (f_ptr == NULL)
    {
        perror("Not able to open proc/meminfo file");
        return;
    }

    int i = 0;
    char *input_buffer = (char *)calloc(MAX_STR_LEN, sizeof(char));
    while (fgets((input_buffer), 256, f_ptr))
    {
        // SwapTotal:       2097148 kB
        // SwapFree:        2092540 kB
        // Dirty:               360 kB
        //      :
        i++;
        if (i == 17)
        {
            char **matrix = create_cmd_matrix();
            int num = account_space_and_tab(input_buffer, matrix);
            printf(" %s %s", matrix[num - 2], matrix[num - 1]);
            free(matrix);
            // printf("%s\n", input_buffer);
            break;
        }
    }
    free(input_buffer);

    fflush(stdout);
    fclose(f_ptr);
}
void _baywatch_dirty(int n)
{
    clock_t init_time = clock();
    while (get_input() != 'q')
    {
        clock_t time = (clock() - init_time) / CLOCKS_PER_SEC;
        if (time >= n)
        {
            init_time = clock();
            _baywatch_dirty_helper();
        }
    }
}
void _baywatch(char **ind_cmd_tokens, int no_of_ind_cmds)
{
    if (no_of_ind_cmds != 4)
    {
        perror("Incorrect command");
        return;
    }
    else
    {
        int n = INVALID;
        for (int i = 1; i < no_of_ind_cmds; i++)
        {
            if (strcmp(ind_cmd_tokens[i], "-n") == 0)
            {
                int j = i + 1;
                if (ind_cmd_tokens[j] != NULL && strlen(ind_cmd_tokens[j]) == 1)
                {
                    n = atoi(ind_cmd_tokens[j]);
                    if (n <= 0)
                    {
                        perror("Invalid n");
                        return;
                    }
                }
            }
        }
        for (int i = 1; i < no_of_ind_cmds; i++)
        {
            if (strcmp(ind_cmd_tokens[i], "interrupt") == 0)
            {
                _baywatch_interrupt(n);
                printf("\n");
                return;
            }
            else if (strcmp(ind_cmd_tokens[i], "newborn") == 0)
            {
                _baywatch_newborn(n);
                printf("\n");
                return;
            }
            else if (strcmp(ind_cmd_tokens[i], "dirty") == 0)
            {
                _baywatch_dirty(n);
                printf("\n");
                return;
            }
        }
        perror("Incorrect command");
        return;
    }
}