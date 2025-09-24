#include "ft_ping.h"

extern t_answer *answer;
volatile sig_atomic_t alarm_flag = 0;

void handleAlarm(int signal) {
	(void) signal;
	alarm_flag = 1;
}

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
    signal(SIGALRM, handleAlarm);
	bool isCount = data->isCount;
	unsigned int count = 0;
	if (isCount)
		count = data->count;
	int interval = data->interval;
	free(data);
	alarm(interval);
	
    while (true)
    {
		fd_set read_fds;
		FD_ZERO(&read_fds);
		FD_SET(answer->socketFd, &read_fds);
        
		struct timeval timeout;
		timeout.tv_sec = 0;
		timeout.tv_usec = 100000;
		
		int ready = select(answer->socketFd + 1, &read_fds, NULL, NULL, &timeout);
		if (ready > 0)
		{	
			receivePing(answer);
			if (answer->sent)
				printPing(answer);
		}
		
		if (alarm_flag) {
			alarm_flag = 0;
			alarm(interval);
			sendPing(answer);
			if (isCount && answer->icmp_ind >= count)
				exitOnCount(answer);

			answer->icmp_ind++;
		}

    }
	return 0;
}
