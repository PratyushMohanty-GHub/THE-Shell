#include "global.h"

int main(int argc, char const *argv[])
{
    init_shell_prompt();
    while (1)
    {
        print_shell_prompt();
        fetch_and_execute_next_ins();
    }
    write_back_history();
    return 0;
}