#include "../global.h"
#include "replay.h"

void _replay(char **ind_cmd_tokens, int no_of_tokens_in_cmd)
{
    int k = 0;
    int period, interval;

    char *temp_cmd[100];
    for (int i = 1; i < no_of_tokens_in_cmd; i++)
    {
        if (strcmp(ind_cmd_tokens[i], "-command") == 0)
        {
            int j = i + 1;
            while (ind_cmd_tokens[j] != NULL && ind_cmd_tokens[j][0] != '-')
            {
                temp_cmd[k] = ind_cmd_tokens[j];
                k++;
                j++;
            }
        }
        if (strcmp(ind_cmd_tokens[i], "-interval") == 0)
        {
            interval = atoi(ind_cmd_tokens[i + 1]);
        }
        if (strcmp(ind_cmd_tokens[i], "-period") == 0)
        {
            period = atoi(ind_cmd_tokens[i + 1]);
        }
    }

    // clock_t initTime = clock();
    // while (true)
    // {
    //     clock_t time = (clock() - initTime) / CLOCKS_PER_SEC;
    //     clock_t finalTime = clock() / CLOCKS_PER_SEC;

    //     if (finalTime > period)
    //         break;

    //     if (time >= interval)
    //     {
    //         initTime = clock();
    //         execute_cmd(temp_cmd, k);
    //     }
    // }

    int remainder_interval = period % interval;
    int no_of_times = period / interval;
    for (int i = 0; i < no_of_times; i++)
    {
        sleep(interval);
        execute_cmd(temp_cmd, k);
    }
    sleep(remainder_interval);
}