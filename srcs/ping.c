#include "ft_ping.h"

unsigned short checksum(void *b, int len)
{
    unsigned short *buf = b;
    unsigned int sum = 0;
    unsigned short result;

    for (sum = 0; len > 1; len -= 2)
        sum += *buf++;
    if (len == 1)
        sum += *(unsigned char *)buf;
    sum = (sum >> 16) + (sum & 0xFFFF);
    sum += (sum >> 16);
    result = ~sum;
    return result;
}

void    sendPing(t_answer *answer)
{
    struct icmp_header *icmp = (struct icmp_header *)answer->packet;
    
    icmp->type = ICMP_HEADER_SIZE;
    icmp->code = 0;
    icmp->checksum = 0;
    icmp->identifier = getpid() & 0xFFFF;
    icmp->sequence = answer->icmp_ind;
    icmp->checksum = checksum(answer->packet, PACKET_SIZE);
    start_time(answer);
    int sent = sendto(answer->socketFd, answer->packet, PACKET_SIZE, 0, (struct sockaddr *)&answer->dest, sizeof(answer->dest));
    if (sent < 0) {
	    printf("Timeout\n");
	}
    answer->packets_transmitted++;
}

void    receivePing(t_answer *answer)
{
    struct sockaddr_in from;
	socklen_t fromlen = sizeof(from);
    char recv_packet[PACKET_SIZE];
    answer->received = recvfrom(answer->socketFd, recv_packet, PACKET_SIZE, 0, (struct sockaddr *)&from, &fromlen);
    if (answer->received == -1) {
        answer->timeout = true;
        answer->packet_loss++;
	} else {
        get_time(answer);
        set_round_trip(answer);
        answer->timeout = false;
        answer->ip = (struct ip *)recv_packet;
        int ip_header_len = answer->ip->ip_hl * 4;
        answer->icmp = (struct icmp_header *)(recv_packet + ip_header_len);
        checkIcmpType(answer);
	}
}

void    checkIcmpType(t_answer *answer)
{
    if (answer->icmp->type == 11) {
        answer->packet_loss++;
        answer->timeout = true;
    }
    else
        answer->packets_received++;
}