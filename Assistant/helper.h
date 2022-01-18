#ifndef _HELPER_H_
#define _HELPER_H_

void get_rel_path(char *abs_path, char *rel_path);
char **create_cmd_matrix();
char get_process_status(pid_t pro_id);

#endif