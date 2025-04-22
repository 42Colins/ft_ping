#include "ft_ping.h"

void	freeDuringInit(t_answer *answer, t_ping *ping)
{
	free(answer);
	free(ping);
	exit(1);
}
