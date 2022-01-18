#include "../global.h"
#include "ls.h"

void _ls_helper(char *dir_name, int flag_a, int flag_l)
{
    struct dirent *dir;
    if (dir_name[strlen(dir_name) - 1] == '/')
        dir_name[strlen(dir_name) - 1] = '\0';

    DIR *dir_ptr = opendir(dir_name);
    if (dir_ptr == NULL)
    {
        if (errno == ENOENT)
        {
            perror("Directory does not exist");
        }
        else
        {
            perror("Unable to read directory");
        }
        // exit(EXIT_FAILURE);
        return;
    }
    struct stat buf;
    if (flag_a == 0 && flag_l == 0)
    {
        while ((dir = readdir(dir_ptr)) != NULL)
        {
            if (dir->d_name[0] == '.')
                continue;
            printf(" %s\n", dir->d_name);
        }
        printf("\n");
    }
    else if (flag_a == 1 && flag_l == 0)
    {
        while ((dir = readdir(dir_ptr)) != NULL)
        {
            printf(" %s\n", dir->d_name);
        }
        printf("\n");
    }
    else if (flag_a == 0 && flag_l == 1)
    {
        int total = 0;
        while ((dir = readdir(dir_ptr)) != NULL)
        {
            // Problem lies here start starting corr here
            char subdir_path[10000] = "";
            strcpy(subdir_path, dir_name);
            strcat(subdir_path, "/");
            strcat(subdir_path, dir->d_name);
            stat(subdir_path, &buf);
            // Problem lies here end
            if (dir->d_name[0] != '.')
                total += (buf.st_blocks / 2);
        }
        printf("total %d\n", total);

        dir_ptr = opendir(dir_name);
        while ((dir = readdir(dir_ptr)) != NULL)
        {
            // ONLY NON_WORKING PART IN LS(ls -l dir_name) STARTS
            // if (dir->d_name[0] == '.')
            // {
            //     continue;
            // }
            // ONLY NON_WORKING PART IN LS(ls -l dir_name) ENDS

            // problem starts here starting corr here
            char subdir_path[10000] = "";
            strcpy(subdir_path, dir_name);
            strcat(subdir_path, "/");
            strcat(subdir_path, dir->d_name);
            stat(subdir_path, &buf);
            // problem ends here

            char mod[10];
            mod[0] = ((buf.st_mode & S_IFDIR) ? 'd' : '-');
            mod[1] = ((buf.st_mode & S_IRUSR) ? 'r' : '-');
            mod[2] = ((buf.st_mode & S_IWUSR) ? 'w' : '-');
            mod[3] = ((buf.st_mode & S_IXUSR) ? 'x' : '-');
            mod[4] = ((buf.st_mode & S_IRGRP) ? 'r' : '-');
            mod[5] = ((buf.st_mode & S_IWGRP) ? 'w' : '-');
            mod[6] = ((buf.st_mode & S_IXGRP) ? 'x' : '-');
            mod[7] = ((buf.st_mode & S_IROTH) ? 'r' : '-');
            mod[8] = ((buf.st_mode & S_IWOTH) ? 'w' : '-');
            mod[9] = ((buf.st_mode & S_IXOTH) ? 'x' : '-');

            char *ctime();
            char *tmps = ctime(&buf.st_mtime);
            tmps[strlen(tmps) - 1] = ' ';

            char *time_str = calloc(13, sizeof(char));
            for (int i = 0; i < 12; i++)
            {
                time_str[i] = tmps[4 + i];
            }

            struct passwd *pw = getpwuid(buf.st_uid);
            struct group *gr = getgrgid(buf.st_gid);

            if (dir->d_name[0] != '.')
            {
                for (int i = 0; i < 10; i++)
                    printf("%c", mod[i]);

                printf(" %2ld %s %s %5ld %s  %s \n", buf.st_nlink, pw->pw_name, gr->gr_name, buf.st_size, time_str, dir->d_name);
            }
            free(time_str);
        }
    }
    else
    {
        int total = 0;
        while ((dir = readdir(dir_ptr)) != NULL)
        {
            // problem starts here
            char subdir_path[10000] = "";
            strcpy(subdir_path, dir_name);
            strcat(subdir_path, "/");
            strcat(subdir_path, dir->d_name);
            stat(subdir_path, &buf);
            // problem ends here
            total += (buf.st_blocks / 2);
        }
        printf("total %d\n", total);

        dir_ptr = opendir(dir_name);
        while ((dir = readdir(dir_ptr)) != NULL)
        {
            // problem starts here
            char subdir_path[10000] = "";
            strcpy(subdir_path, dir_name);
            strcat(subdir_path, "/");
            strcat(subdir_path, dir->d_name);
            stat(subdir_path, &buf);
            // problem ends here

            char mod[10];
            mod[0] = ((buf.st_mode & S_IFDIR) ? 'd' : '-');
            mod[1] = ((buf.st_mode & S_IRUSR) ? 'r' : '-');
            mod[2] = ((buf.st_mode & S_IWUSR) ? 'w' : '-');
            mod[3] = ((buf.st_mode & S_IXUSR) ? 'x' : '-');
            mod[4] = ((buf.st_mode & S_IRGRP) ? 'r' : '-');
            mod[5] = ((buf.st_mode & S_IWGRP) ? 'w' : '-');
            mod[6] = ((buf.st_mode & S_IXGRP) ? 'x' : '-');
            mod[7] = ((buf.st_mode & S_IROTH) ? 'r' : '-');
            mod[8] = ((buf.st_mode & S_IWOTH) ? 'w' : '-');
            mod[9] = ((buf.st_mode & S_IXOTH) ? 'x' : '-');

            char *ctime();
            char *tmps = ctime(&buf.st_mtime);
            tmps[strlen(tmps) - 1] = ' ';

            char *time_str = calloc(13, sizeof(char));
            for (int i = 0; i < 12; i++)
            {
                time_str[i] = tmps[4 + i];
            }

            struct passwd *pw = getpwuid(buf.st_uid);
            struct group *gr = getgrgid(buf.st_gid);

            for (int i = 0; i < 10; i++)
                printf("%c", mod[i]);
            printf(" %2ld %s %s %5ld %s  %s \n", buf.st_nlink, pw->pw_name, gr->gr_name, buf.st_size, time_str, dir->d_name);
            free(time_str);
        }
    }
    closedir(dir_ptr);
}
void _ls(char **ind_cmd_tokens, int no_of_ind_cmds)
{
    if (no_of_ind_cmds == 1)
    {
        _ls_helper(".", 0, 0);
    }
    else
    {
        // -> ls - <flags> <Directory/File_name>
        // -> ls -l <dir_1> -a <dir_2>
        // If Multiple directories names -> print name of directories

        int flag_a = 0, flag_l = 0;

        int no_of_files = 0;
        char **file_list = (char **)calloc(MAX_PATH_LEN, sizeof(char *));
        for (int i = 1; i < no_of_ind_cmds; i++)
        {
            if (ind_cmd_tokens[i][0] == '-')
            {
                if (strcmp(ind_cmd_tokens[i], "-l") == 0 || strcmp(ind_cmd_tokens[i], "-al") == 0 || strcmp(ind_cmd_tokens[i], "-la") == 0)
                    flag_l = 1;
                if (strcmp(ind_cmd_tokens[i], "-a") == 0 || strcmp(ind_cmd_tokens[i], "-al") == 0 || strcmp(ind_cmd_tokens[i], "-la") == 0)
                    flag_a = 1;
            }
            else
            {
                file_list[no_of_files] = ind_cmd_tokens[i];
                no_of_files++;
            }
        }

        if (no_of_files == 0)
        {
            _ls_helper(".", flag_a, flag_l);
        }
        for (int i = 0; i < no_of_files; i++)
        {
            if (no_of_files > 1)
                printf("%s:\n", file_list[i]);
            if (strcmp(file_list[i], "~") == 0)
            {
                _ls_helper(abs_home_dir_path, flag_a, flag_l);
            }
            else
            {
                _ls_helper(file_list[i], flag_a, flag_l);
            }

            if (no_of_files > 1 && i != no_of_files - 1)
                printf("\n");
        }
        free(file_list);
    }
}