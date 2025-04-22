#include "ft_ping.h"

void	initPrint(t_answer *ping)
{
	printf("PING %s (%s): %d data bytes\n", ping->address, ping->addressN, ping->bytes_sent - 8);
}

void	endPrint(t_answer *ping)
{
	printf("--- %s ping statistics ---\n", ping->address);
	printf("%d packets transmitted, %d packets received, %u%% packet loss, time %f\n", ping->packets_transmitted, ping->packets_received, (ping->packets_transmitted - ping->packets_received) * 100 / ping->packets_transmitted, ping->total_time);
	if (((ping->packets_transmitted - ping->packets_received) * 100 / ping->packets_transmitted) != 100)
		printf("round-trip min/avg/max/mdev = %.3f/%.3f/%.3f/%.3f ms\n", ping->min_time, ping->total_time / ping->packets_received, ping->max_time, ping->mdev);
}

void	printPing(t_answer *ping)
{
	if (!ping->timeout)
		printf("%d bytes from %s: icmp_seq=%d ttl=%d time=%.3f ms\n", ping->bytes_sent, ping->reversednsAddress, ping->icmp_ind, ping->ttl, ping->time);
	else
		printf("Request timeout for icmp_seq %d\n", ping->icmp_ind);
}

void	printVerbosePing(t_answer *ping)
{
	printf("ICMP: type=%d, code=%d, checksum=%d\n", 
		ping->icmp_ind >> 8, ping->icmp_ind & 0xFF, ping->ttl);
	printf("IP: ttl=%d, protocol=%d, length=%d\n", 
		ping->ttl, IPPROTO_ICMP, ping->bytes_sent);
}

void	printHelpPing(void)
{
	printf("usage: ping [options] destination\n            -v:	verbose output\n");
}