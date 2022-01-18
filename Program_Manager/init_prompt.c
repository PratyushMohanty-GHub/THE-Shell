#include "../global.h"
#include "init_prompt.h"

void print_welcome_line()
{
    for (int i = 0; i < 5; i++)
        printf("\t");

    printf("***** ");
    print_bold_in_red;
    printf("Welcome to");
    print_in_green;
    printf(" T");
    print_in_cyan;
    printf("H");
    print_in_white;
    printf("E");
    print_bold_in_red;
    printf("-Shell");
    print_in_white;
    printf(" *****\n\n");
}
void init_shell_prompt()
{
    printf("\033[H\033[J");
    abs_home_dir_path = (char *)calloc(MAX_PATH_LEN, sizeof(char));
    rel_home_dir_path = (char *)calloc(MAX_PATH_LEN, sizeof(char));
    getcwd(abs_home_dir_path, MAX_STR_LEN);
    get_rel_path(abs_home_dir_path, rel_home_dir_path);

    abs_prev_dir_path = (char *)calloc(MAX_PATH_LEN, sizeof(char));
    rel_prev_dir_path = (char *)calloc(MAX_PATH_LEN, sizeof(char));
    getcwd(abs_prev_dir_path, MAX_STR_LEN);
    get_rel_path(abs_prev_dir_path, rel_prev_dir_path);

    abs_history_path = (char *)calloc(MAX_PATH_LEN, sizeof(char));
    strcpy(abs_history_path, abs_home_dir_path);
    strcat(abs_history_path, "/THE_history");

    // For upArrow key
    up_last_input = (char *)calloc(MAX_PATH_LEN, sizeof(char));

    // For managing History
    history_list = (char **)calloc(20, sizeof(char *));
    for (int i = 0; i < 20; i++)
    {
        history_list[i] = (char *)calloc(MAX_STR_LEN, sizeof(char));
        strcpy(history_list[i], "_NULL_");
    }

    FILE *hist_file = fopen(abs_history_path, "r");
    if (hist_file == NULL)
    {
        hist_file = fopen(abs_history_path, "w");
    }
    else
    {
        read_history();
    }
    no_of_elem_in_history = 0;
    last_seen_idx = 20;

    // For managing bg_process
    init_job_list();
    // For managing fg_process
    init_fg_job_list();

    // For signals when a child process terminates
    init_exit_signal();
    // For handling Ctrl + C and Ctrl + Z signals
    handle_other_signals();

    // Create a copy of the INPUT file descriptor
    STD_INP_DUP = dup(STDIN_FILENO);
    // Create a copy of the OUTPUT file descriptor
    STD_OUT_DUP = dup(STDOUT_FILENO);

    print_welcome_line();
}
