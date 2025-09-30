#include "ft_ping.h"

t_answer *answer;

void    handleSignal(int signal)
{
    (void) signal;
	printf("\n");
    if (answer)
    {
        endPrint(answer);
        if (answer->packet)
            free(answer->packet);
        if (answer->addressN)
            free(answer->addressN);
        if (answer->hostname)
            free(answer->hostname);
        if (answer->selfAddress)
            free(answer->selfAddress);
        if (answer->sender_address)
            free(answer->sender_address);
        free(answer);
    }
    exit(0);
}