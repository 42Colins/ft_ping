#include "ft_ping.h"

bool	start_time(t_answer *ping)
{
	struct timeval time;
	if (gettimeofday(&time, NULL) == -1)
		return (-1);
	ping->start_time = (time.tv_sec * 1000000) + time.tv_usec;
	printf("DEBUG: Start time recorded: %ld.%06ld\n", ping->start_time / 1000000, ping->start_time % 1000000);
	return (0);
}

bool	get_time(t_answer *ping)
{
	struct timeval time;
	if (gettimeofday(&time, NULL) == -1)
		return (-1);
	double current_time = (time.tv_sec * 1000000) + time.tv_usec;
	// printf("Current time: %f us\n", current_time);
	// printf("Start time: %ld us\n", ping->start_time);
	ping->time = (current_time - ping->start_time) / 1000.0;
	// printf("Elapsed time: %f ms\n", ping->time);
	return (0);
}

void    set_round_trip(t_answer *answer)
{
    answer->total_time += answer->time;
	answer->total_time_squared += answer->time * answer->time;
    if (answer->icmp_ind == 0)
    {   
        answer->min_time = answer->time;
        answer->max_time = answer->time;
    }
    if (answer->time < answer->min_time)
        answer->min_time = answer->time;
    if (answer->time > answer->max_time)
		{answer->max_time = answer->time;}
	answer->med_time = answer->total_time / answer->packets_received;

}