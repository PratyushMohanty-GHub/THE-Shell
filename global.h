#ifndef _GLOBAL_H_
#define _GLOBAL_H_

#define MAX_STR_LEN 5000
#define MAX_PATH_LEN 5000

char *rel_home_dir_path;
char *abs_home_dir_path;

char *rel_prev_dir_path;
char *abs_prev_dir_path;

#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>

#include <sys/wait.h>
#include <sys/file.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/utsname.h>

#include <grp.h>
#include <pwd.h>
#include <time.h>

#include "Shell_Commands/cd.h"
#include "Shell_Commands/ls.h"
#include "Shell_Commands/pwd.h"
#include "Shell_Commands/jobs.h"
#include "Shell_Commands/echo.h"
#include "Shell_Commands/pinfo.h"
#include "Shell_Commands/replay.h"
#include "Shell_Commands/repeat.h"
#include "Shell_Commands/fgbgsig.h"
#include "Shell_Commands/sys_cmds.h"
#include "Shell_Commands/baywatch.h"
#include "Shell_Commands/up_arrow.h"

#include "Program_Manager/fetch.h"
#include "Program_Manager/input.h"
#include "Program_Manager/signal.h"
#include "Program_Manager/piping.h"
#include "Program_Manager/execute.h"
#include "Program_Manager/history.h"
#include "Program_Manager/tokenize.h"
#include "Program_Manager/init_prompt.h"
#include "Program_Manager/print_prompt.h"
#include "Program_Manager/io_redirection.h"

#include "Assistant/color.h"
#include "Assistant/helper.h"
#include "Assistant/sorter.h"

#define true 1
#define false 0

#endif