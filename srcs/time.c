#include "ft_ping.h"

static double packet_start_time = 0;

bool	start_time(t_answer *ping)
{
	(void)ping;  // Unused parameter
	struct timeval time;
	if (gettimeofday(&time, NULL) == -1)
		return (-1);
	packet_start_time = (time.tv_sec * 1000000) + time.tv_usec;
	return (0);
}

bool	get_time(t_answer *ping)
{
	struct timeval time;
	if (gettimeofday(&time, NULL) == -1)
		return (-1);
	double current_time = (time.tv_sec * 1000000) + time.tv_usec;
	ping->time = (current_time - packet_start_time) / 1000.0;
	return (0);
}

void    set_round_trip(t_answer *answer)
{
    answer->total_time += answer->time;
	answer->total_time_squared += answer->time * answer->time;
    if (answer->icmp_ind == 1)
    {
        answer->min_time = answer->time;
        answer->max_time = answer->time;
    }
    if (answer->time < answer->min_time)
        answer->min_time = answer->time;
    if (answer->time > answer->max_time)
		answer->max_time = answer->time;
}