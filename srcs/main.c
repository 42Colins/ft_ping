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
		if (data->isCount)
		{
			if (answer->icmp_ind + 1 == data->count)
				exitOnCount(answer);
		}
		if (!answer->timeout || answer->verboseError)
	        sleep(data->interval);
        answer->icmp_ind++;
    }
	return 0;
}
