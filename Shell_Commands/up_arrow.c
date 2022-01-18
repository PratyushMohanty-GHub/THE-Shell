#include "../global.h"
#include "up_arrow.h"

void up_arrow_cmd()
{
    if (last_seen_idx > 0)
    {
        --last_seen_idx;
    }
    if (strcmp(history_list[last_seen_idx], "_NULL_") != 0)
    {
        printf("%s", history_list[last_seen_idx]);
        strcpy(up_last_input, history_list[last_seen_idx]);
    }
    else
    {
        ++last_seen_idx;
        printf("%s", history_list[last_seen_idx]);
        strcpy(up_last_input, history_list[last_seen_idx]);
    }
}