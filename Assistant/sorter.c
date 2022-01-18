#include "../global.h"
#include "sorter.h"

void sort_struct_array(proc jobs[], int no_of_jobs)
{
    for (int i = 1; i < no_of_jobs; i++)
    {
        for (int j = 0; j < no_of_jobs - i; j++)
        {
            if (strcmp(jobs[j].proc_name, jobs[j + 1].proc_name) > 0)
            {
                proc temp = jobs[j];
                jobs[j] = jobs[j + 1];
                jobs[j + 1] = temp;
            }
        }
    }
}
