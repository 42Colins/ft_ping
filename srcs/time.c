#include "ft_ping.h"

bool	start_time(t_answer *ping)
{
	struct timeval time;
	if (gettimeofday(&time, NULL) == -1)
		return (-1);
	ping->start_time = (time.tv_sec * 1000000) + time.tv_usec;
	// printf("starting time = %f\n", ping->start_time);
	return (0);
}

bool	get_time(t_answer *ping)
{
	struct timeval time;
	if (gettimeofday(&time, NULL) == -1)
		return (-1);
	double current_time = (time.tv_sec * 1000000) + time.tv_usec;
	ping->time = (current_time - ping->start_time) / 1000.0;
	// printf("current_time = %f\n", current_time);
	// printf("start_time = %f\n", ping->start_time);
	// printf("time = %f\n", ping->time);
	// printf("time = %f index = %d\n", ping->time, ping->icmp_ind);
	return (0);
}

void    set_round_trip(t_answer *answer)
{
	// printf("answer->time = %f\n", answer->time);
    answer->total_time += answer->time;
	// printf("total_time = %f\n", answer->total_time);
	answer->total_time_squared += answer->time * answer->time;
    if (answer->icmp_ind == 1)
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