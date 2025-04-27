#include "ft_ping.h"

void	freeDuringInit(t_answer *answer, t_ping *ping)
{
	free(answer);
	free(ping);
	exit(1);
}

void	exitOnCount(t_answer *answer)
{
    if (answer)
    {
        endPrint(answer);
        if (answer->packet)
            free(answer->packet);
        if (answer->addressN)
            free(answer->addressN);
        free(answer);
    }
    exit(0);
}