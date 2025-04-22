#include "ft_ping.h"

bool	start_time(t_answer *ping)
{
	struct timeval time;
	if (gettimeofday(&time, NULL) == -1)
		return (-1);
	ping->start_time = (time.tv_sec * 1000000) + time.tv_usec;
	return (0);
}

bool	get_time(t_answer *ping)
{
	struct timeval time;
	if (gettimeofday(&time, NULL) == -1)
		return (-1);
	double current_time = (time.tv_sec * 1000000) + time.tv_usec;
	ping->time = (current_time - ping->start_time) / 1000.0; // Convert to milliseconds with decimal precision
	return (0);
}

void    set_round_trip(t_answer *answer)
{
    answer->time_array = realloc(answer->time_array, answer->icmp_ind * sizeof(double));
    answer->total_time += answer->time;
    if (answer->icmp_ind == 0)
    {   
        answer->min_time = answer->time;
        answer->max_time = answer->time;
    }
    if (answer->time < answer->min_time)
        answer->min_time = answer->time;
    if (answer->time > answer->max_time)
        answer->max_time = answer->time;
	answer->time_array[answer->icmp_ind] = answer->time;
	answer->med_time = answer->total_time / answer->packets_received;
	double mean = 0;
	for (unsigned int i = 0; i < answer->icmp_ind; i++)
	{
		if (answer->time_array[i] != 0)
			mean += fabs(answer->time_array[i] - answer->med_time);
	}
    answer->mdev = mean / answer->packets_received;
}