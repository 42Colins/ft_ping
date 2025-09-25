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
    
    icmp->type = ICMP_ECHO;
    icmp->code = 0;
    icmp->checksum = 0;
    icmp->identifier = getpid() & 0xFFFF;
    icmp->sequence = answer->icmp_ind;
    icmp->checksum = checksum(answer->packet, PACKET_SIZE);
    start_time(answer);
    int sent = sendto(answer->socketFd, answer->packet, PACKET_SIZE, 0, (struct sockaddr *)&answer->dest, sizeof(answer->dest));
    if (sent < 0)
        answer->sent = false;
    else 
        answer->sent = true;
    answer->packets_transmitted++;
}

void receivePing(t_answer *answer)
{
    static char recv_packet[PACKET_SIZE];
    static struct ip null_ip;
    static struct icmp_header null_icmp;
    memset(recv_packet, 0, PACKET_SIZE);

    struct sockaddr_in from;
    socklen_t fromlen = sizeof(from);
    ssize_t bytes_received = recvfrom(answer->socketFd, recv_packet, PACKET_SIZE, 
                                      MSG_DONTWAIT, (struct sockaddr*)&from, &fromlen);
    if (bytes_received < 0) {
        answer->timeout = true;
        answer->packet_loss++;
        memset(&null_ip, 0, sizeof(null_ip));
        memset(&null_icmp, 0, sizeof(null_icmp));
        answer->ip = &null_ip;
        answer->icmp = &null_icmp;
        if (answer->sender_address) {
            free(answer->sender_address);
            answer->sender_address = NULL;
        }
        get_time(answer);
        set_round_trip(answer);
    } else {
        get_time(answer);
        set_round_trip(answer);
        answer->timeout = false;
        answer->ip = (struct ip *)recv_packet;
        int ip_header_len = answer->ip->ip_hl * 4;
        answer->received_ttl = answer->ip->ip_ttl;
        if (answer->sender_address) 
            free(answer->sender_address);
        answer->sender_address = strdup(inet_ntoa(from.sin_addr));
        answer->icmp = (struct icmp_header *)(recv_packet + ip_header_len);
        
        checkIcmpType(answer);
    }
}

void checkIcmpType(t_answer *answer)
{
    if (!answer->icmp)
        return;
    
    if (answer->icmp->type == ICMP_ECHOREPLY) {
        answer->packets_received++;
        return;
    }
    if (answer->icmp->type == ICMP_TIME_EXCEEDED) {
        // answer->timeout = false;
        answer->timeout = true;
        answer->packets_received++;
        answer->ttlExceeded = true;
        return;
    }
    if (answer->icmp->type == ICMP_DEST_UNREACH) {
        answer->unreachable = true;
        answer->timeout = true;
        answer->packet_loss++;
        return;
    }
    answer->timeout = true;
    answer->packet_loss++;
}