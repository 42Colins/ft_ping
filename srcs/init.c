#include "ft_ping.h"

t_answer *initPing(t_ping *ping, t_answer *answer)
{
    answer = (t_answer *)malloc(sizeof(t_answer));
    if (!answer)
        return (NULL);
    initAnswer(answer, ping);
    initPrint(answer);
    return (answer);
}

void    initAnswer(t_answer *answer, t_ping *ping)
{
	answer->verbose = ping->verbose;
    answer->bytes_sent = PACKET_SIZE;
    answer->address = ping->address;
    answer->icmp_ind = 0;
    answer->socketFd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
    if (answer->socketFd < 0)
        freeDuringInit(answer, ping);
    answer->packets_transmitted = 0;
    answer->packets_received = 0;
    answer->min_time = 0;
    answer->max_time = 0;
    answer->total_time = 0;
	answer->id = getpid();
    setSocket(answer, ping);
    getAddress(answer, ping);
    getDnsAddress(answer, ping);
}

void    setSocket(t_answer *answer, t_ping *ping)
{
    int ttl = 1;
    struct timeval error;
    error.tv_sec = 1;
    error.tv_usec = 0;
   if (setsockopt(answer->socketFd, SOL_SOCKET, SO_RCVTIMEO, &error, sizeof(error)) < 0)
        freeDuringInit(answer, ping);
    if (setsockopt(answer->socketFd, IPPROTO_IP, IP_TTL, &ttl, sizeof(ttl)) < 0)
        freeDuringInit(answer, ping);
    answer->ttl = ttl;
	printf("set socket %d\n", answer->ttl);
    answer->packet = malloc(PACKET_SIZE);
    if (!answer->packet)
        freeDuringInit(answer, ping);
}

void    getAddress(t_answer *answer, t_ping *ping)
{
    memset(answer->packet, 0, PACKET_SIZE);
    memset(&answer->dest, 0, sizeof(answer->dest));
    answer->dest.sin_family = AF_INET;
    if (inet_pton(AF_INET, ping->address, &answer->dest.sin_addr) <= 0) {
        struct hostent *host = gethostbyname(ping->address);
        if (!host) 
            freeDuringInit(answer, ping);
        memcpy(&answer->dest.sin_addr, host->h_addr, host->h_length);
    }
    answer->addressN = strdup(inet_ntoa(answer->dest.sin_addr));
    if (!answer->addressN)
        freeDuringInit(answer, ping);
}

void    getDnsAddress(t_answer *answer, t_ping *ping)
{
    answer->reversednsAddress = malloc(1024);
    if (!answer->reversednsAddress)
        freeDuringInit(answer, ping);
    struct sockaddr_in revdns;
    memset(&revdns, 0, sizeof(revdns));
    revdns.sin_family = AF_INET;
    revdns.sin_addr = answer->dest.sin_addr;
    int err = getnameinfo((struct sockaddr *)&revdns, sizeof(revdns), answer->reversednsAddress, 1024, NULL, 0, NI_NAMEREQD);
    if (err != 0)
        freeDuringInit(answer, ping);
}