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
    if (ping->isTos)
    {
        answer->tos = ping->tos;
        answer->isTos = ping->isTos;
    }
    else
        answer->tos = 0;
    answer->ttlExceeded = false;
    answer->unreachable = false;    
    answer->stddev = 0;
    answer->packet_loss = 0;
    answer->sent = true;
    answer->size = ping->size;
	answer->ttl = ping->ttl;
	answer->verbose = ping->verbose;
	answer->verboseError = false;
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
    answer->total_time_squared = 0;
	answer->id = getpid();
    answer->timeout = false;
    setSocket(answer, ping);
    getAddress(answer, ping);
    getSelfAddress(answer, ping);
}

void    setSocket(t_answer *answer, t_ping *ping)
{
    // int broadcast = 1;
    int on = 1;
    struct timeval error;
    error.tv_sec = 1;
    error.tv_usec = 0;
    if (setsockopt(answer->socketFd, SOL_SOCKET, SO_RCVTIMEO, &error, sizeof(error)) < 0)
        freeDuringInit(answer, ping);
    if (setsockopt(answer->socketFd, IPPROTO_IP, IP_TTL, &answer->ttl, sizeof(answer->ttl)) < 0)
        freeDuringInit(answer, ping);
    if (setsockopt(answer->socketFd, IPPROTO_IP, IP_RECVERR, &on, sizeof(on)) < 0)
        freeDuringInit(answer, ping);
    if (setsockopt(answer->socketFd, IPPROTO_IP, IP_RECVTTL, &on, sizeof(on)) < 0)
        freeDuringInit(answer, ping);
    // if (setsockopt(answer->socketFd, SOL_SOCKET, SO_BROADCAST, &broadcast, sizeof(broadcast)) < 0)
    //     freeDuringInit(answer, ping);
    if (ping->isTos)
    {
        if (setsockopt(answer->socketFd, IPPROTO_IP, IP_TOS, &ping->tos, sizeof(ping->tos)) < 0)
            freeDuringInit(answer, ping);
    }
    answer->packet = malloc(ping->size);
    if (!answer->packet)
        freeDuringInit(answer, ping);
}

void getAddress(t_answer *answer, t_ping *ping)
{
    struct addrinfo hints;
    struct addrinfo *result;
    int status;

    memset(answer->packet, 0, PACKET_SIZE);
    memset(&answer->dest, 0, sizeof(answer->dest));
    
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_RAW;
    
    status = getaddrinfo(ping->address, NULL, &hints, &result);
    if (status != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(status));
        freeDuringInit(answer, ping);
    }
    
    if (result != NULL) {
        struct sockaddr_in *ipv4 = (struct sockaddr_in *)result->ai_addr;
        answer->dest.sin_family = AF_INET;
        answer->dest.sin_addr = ipv4->sin_addr;        
        answer->addressN = strdup(inet_ntoa(ipv4->sin_addr));
        if (!answer->addressN) {
            freeaddrinfo(result);
            freeDuringInit(answer, ping);
        }
        freeaddrinfo(result);
    } else {
        freeDuringInit(answer, ping);
    }
}

void    getSelfAddress(t_answer *answer, t_ping *ping)
{
    struct ifaddrs *interfaces = NULL;
    struct ifaddrs *ifa = NULL;
    char ip_address[INET_ADDRSTRLEN];  
    char host[NI_MAXHOST];
    struct sockaddr_in sa;
    memset(&sa, 0, sizeof(sa));
    sa.sin_family = AF_INET;
    bool found = false;

    if (getifaddrs(&interfaces) == -1)
        freeDuringInit(answer, ping);
    for (ifa = interfaces; ifa != NULL; ifa = ifa->ifa_next) {
        if (ifa->ifa_addr && ifa->ifa_addr->sa_family == AF_INET) {
            if (found)
                free(answer->hostname);
            void *tmpAddrPtr = &((struct sockaddr_in *)ifa->ifa_addr)->sin_addr;
            inet_ntop(AF_INET, tmpAddrPtr, ip_address, sizeof(ip_address));
            sa.sin_addr = ((struct sockaddr_in *)ifa->ifa_addr)->sin_addr;
            if (getnameinfo((struct sockaddr*)&sa, sizeof(sa), host, sizeof(host), NULL, 0, 0) == 0) {
                answer->hostname = strdup(host);
                found = true;
            }
        }
    }
    
    answer->selfAddress = strdup(ip_address);
    freeifaddrs(interfaces);
}
