#include "../global.h"
#include "print_prompt.h"

void print_prompt_line(char *username, char *host_name, char *rel_curr_dir)
{
    print_in_red;
    printf("<");
    print_in_green;
    printf("%s", username);
    print_in_white;
    printf("@");
    print_in_red;
    printf("%s:", host_name);
    print_in_white;
    printf("%s", rel_curr_dir);
    print_in_red;
    printf("> ");
    print_in_white;
}
void print_shell_prompt()
{
    struct passwd *un = getpwuid(getuid());
    char *username = un->pw_name;

    // USE sys_name for output Linux STARTS

    // struct utsname buf;
    // if (uname(&buf) != 0)
    //     exit(EXIT_FAILURE);
    // char *system_name = buf.sysname;

    // USE sys_name for output Linux ENDS

    char *host_name = (char *)calloc(MAX_STR_LEN, sizeof(char));
    gethostname(host_name, MAX_STR_LEN);
    char *abs_curr_dir = (char *)calloc(MAX_STR_LEN, sizeof(char));
    char *rel_curr_dir = (char *)calloc(MAX_STR_LEN, sizeof(char));
    getcwd(abs_curr_dir, MAX_STR_LEN);
    get_rel_path(abs_curr_dir, rel_curr_dir);

    update_job_status();
    if (curr_no_of_jobs <= 0)
        total_no_of_jobs = 0;

    print_prompt_line(username, host_name, rel_curr_dir);

    free(host_name);
    free(rel_curr_dir);
    free(abs_curr_dir);

    fflush(stdout);
}