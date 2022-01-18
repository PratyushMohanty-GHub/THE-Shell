
#  THE-Shell :  A Simple Interactive Linux Shell 

### Name : Pratyush Mohanty
### Roll No. : 2020101005

## Running the shell

 - #### To Compile the Code with GCC:
``` bash
make
```
 - #### To Run the Shell:
```
./THE_shell
```
 - #### To Exit / Log out from the Shell:
 ```
quit / exit / Ctrl + D
 ```
## Code Organization
### The Entire Code Is Split Into 3 Directories As Follows:

### 1. Program_Manager
Contains implementations of parsing and calling the correct function as per the entered command.

### Files
    - init_prompt.c     - code to initialize the shell prompt at the beginning of the prog
    - print_prompt.c    - code to display <username@system_name:curr_dir>
    - input.c           - for reading cmdline input
    - signal.c          - code to handle different signals like Ctrl + C, Ctrl + Z, Ctrl + D etc.
    - tokenize.c        - code to tokenize the input string 
    - execute.c         - code for calling the right function for the given cmd
    - history.c         - code for managing the shell history
    - fetch.c           - code to check for I/O redirection, Piping and executing each ';' separated command
    - io_redirection.c  - output can be redirected to another file, or the input can be taken from a file other than ​stdin​
    - piping.c          - code to redirect the output of the command on the left as input to the command on the right

### 2. Shell_Commands 
Contains implementations of shell supported semi-colon separated list of commands.  

### Files
    - cd.c              - code for cd command
    - pinfo.c           - code for pinfo command
    - echo.c            - code for echo command
    - pwd.c             - code for pwd command
    - ls.c              - code for ls command
    - repeat.c          - code for repeat command
    - jobs.c            - for user-defined command jobs
    - fgbgsig.c         - for user-defined commands fg, bg & sig.
    - sys_cmds.c        - code for executing system commands 
    - up_arrow.c        - code for implementing up arrow functionality
    - replay.c          - code for replay command
    - baywatch.c        - a modified, very specific version of watch. It exec until the ‘​q’​ key is pressed.

### 3. Assistant
 Contains code to help the other functions in getting relative path of a directory & dynamically allocating memory.

### Files
    - color.h           - adding colors to the output
    - helper.c          - code for getting_rel_path of a dir, allocating memory, get_process_status
    - sorter.c          - code for sorting the bg_processes in alphabetical order of the command name

## Other files in home directory

    - THE_shell : the executable file.
    - THE_history : this file stores all the typed commands in a given order.
    - makefile : compiles the code with GCC to give ./THE_shell an executable file
    - global.h : contains all the user-defined and pre-defined header files.
    - main.c : contains an infinite loop which initializes shell_prompt, prints shell_prompt, fetches and executes the next instruction.