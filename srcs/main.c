#include "ft_ping.h"

extern t_answer *answer;

int main(int argc, char **argv)
{
	if (argc < 2)
	{
		printf("Invalid input to call the ping function\n");
		exit(1);	
	}
	t_ping *data;
	data = parseInputs(argv, argc);
	if (!data)
		return (1);
	answer = initPing(data, answer);
    signal(SIGINT, handleSignal);
    while (true)
    {
        sendPing(data, answer);
        receivePing(data, answer);
        printPing(answer);
		if (!answer->timeout)
	        sleep(1);
		else if (answer->timeout && answer->ttl == 1)
			sleep(1);
        answer->icmp_ind++;
    }
	return 0;
}
