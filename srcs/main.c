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

	if (!isRoot())
	{
		printf("ft_ping: you must be root to run this program\n");
		exit(1);
	}
	t_ping *data;
	data = parseInputs(argv, argc);
	if (!data)
		exit (1);
	double interval = data->interval;
    struct itimerval timer;
    timer.it_value.tv_sec = (int)interval;
    timer.it_value.tv_usec = (interval - (int)interval) * 1000000;
    
    timer.it_interval.tv_sec = timer.it_value.tv_sec;
    timer.it_interval.tv_usec = timer.it_value.tv_usec;
	fd_set read_fds;
    
	answer = initPing(data, answer);
	signal(SIGINT, handleSignal);
    signal(SIGALRM, handleAlarm);
	bool isCount = data->isCount;
	unsigned int count = 0;
	if (isCount)
		count = data->count;
	free(data);
    setitimer(ITIMER_REAL, &timer, NULL);
	answer->done = 255;
	sendPing(answer);
    while (true)
    {
		FD_ZERO(&read_fds);
		FD_SET(answer->socketFd, &read_fds);
        
		struct timeval timeout;
		timeout.tv_sec = 0;
		timeout.tv_usec = 100000;
		if (isCount && answer->icmp_ind == count)
			exitOnCount(answer);
		if (alarm_flag) {
			alarm_flag = 0;
			setitimer(ITIMER_REAL, &timer, NULL);
			sendPing(answer);
			answer->icmp_ind++;
		}

		int ready = select(answer->socketFd + 1, &read_fds, NULL, NULL, &timeout);
		if (ready > 0 && answer->done != answer->icmp_ind)
		{
			answer->done = answer->icmp_ind;
			receivePing(answer);
			if (answer->sent)
				printPing(answer);
		}
    }
	return 0;
}
