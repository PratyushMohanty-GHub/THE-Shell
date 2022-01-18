#include "../global.h"
#include "pwd.h"

char *_pwd()
{
    char *curr_dir = (char *)calloc(MAX_STR_LEN, sizeof(char));
    getcwd(curr_dir, MAX_STR_LEN);
    
    // Print both absolute and relative path
    printf("Absolute Path: %s\n", curr_dir);

    char *rel_path = (char *)calloc(MAX_STR_LEN, sizeof(char));
    get_rel_path(curr_dir, rel_path);

    free(curr_dir);
    return rel_path;
}