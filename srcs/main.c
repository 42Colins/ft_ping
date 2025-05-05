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
	if (!isRoot())
	{
		free(data);
		printf("ft_ping: you must be root to run this program\n");
		exit(1);
	}
	answer = initPing(data, answer);
    signal(SIGINT, handleSignal);
	bool isCount = data->isCount;
	unsigned int count = 0;
	if (isCount)
		count = data->count;
	int interval = data->interval;
	free(data);
    while (true)
    {
        sendPing(answer);
        receivePing(answer);
		if (answer->sent)
	        printPing(answer);
		if (isCount)
		{
			if (answer->icmp_ind + 1 == count)
				exitOnCount(answer);
		}
		if (!answer->timeout || answer->verboseError)
	        sleep(interval);
        answer->icmp_ind++;
    }
	return 0;
}
