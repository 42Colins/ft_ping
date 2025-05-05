#include "ft_ping.h"

#define NITEMS(x) (sizeof(x) / sizeof(x[0]))

typedef struct icmp_code_description_s {
    uint8_t type;
    uint8_t code;
    char *diag;
} icmp_code_description_t;

icmp_code_description_t icmp_code_description[] = {
        {ICMP_DEST_UNREACH, ICMP_NET_UNREACH, "Destination Net Unreachable"},
        {ICMP_DEST_UNREACH, ICMP_HOST_UNREACH, "Destination Host Unreachable"},
        {ICMP_DEST_UNREACH, ICMP_PROT_UNREACH, "Destination Protocol Unreachable"},
        {ICMP_DEST_UNREACH, ICMP_PORT_UNREACH, "Destination Port Unreachable"},
        {ICMP_DEST_UNREACH, ICMP_FRAG_NEEDED, "Fragmentation needed and DF set"},
        {ICMP_DEST_UNREACH, ICMP_SR_FAILED, "Source Route Failed"},
        {ICMP_DEST_UNREACH, ICMP_NET_UNKNOWN, "Network Unknown"},
        {ICMP_DEST_UNREACH, ICMP_HOST_UNKNOWN, "Host Unknown"},
        {ICMP_DEST_UNREACH, ICMP_HOST_ISOLATED, "Host Isolated"},
        {ICMP_DEST_UNREACH, ICMP_NET_UNR_TOS, "Destination Network Unreachable At This TOS"},
        {ICMP_DEST_UNREACH, ICMP_HOST_UNR_TOS, "Destination Host Unreachable At This TOS"},
        {ICMP_REDIRECT, ICMP_REDIR_NET, "Redirect Network"},
        {ICMP_REDIRECT, ICMP_REDIR_HOST, "Redirect Host"},
        {ICMP_REDIRECT, ICMP_REDIR_NETTOS, "Redirect Type of Service and Network"},
        {ICMP_REDIRECT, ICMP_REDIR_HOSTTOS, "Redirect Type of Service and Host"},
        {ICMP_TIME_EXCEEDED, ICMP_EXC_TTL, "Time to live exceeded"},
        {ICMP_TIME_EXCEEDED, ICMP_EXC_FRAGTIME, "Frag reassembly time exceeded"}};

void	initPrint(t_answer *ping)
{
	printf("PING %s (%s): %d data bytes\n", ping->address, ping->addressN, ping->size - 8);
}

void	endPrint(t_answer *ping)
{
	calculate_stddev(ping);
	printf("--- %s ping statistics ---\n", ping->address);
	printf("%d packets transmitted, %d packets received, %u%% packet loss, time %f\n", ping->packets_transmitted, ping->packets_received, (ping->packets_transmitted - ping->packets_received) * 100 / ping->packets_transmitted, ping->total_time);
	if (((ping->packets_transmitted - ping->packets_received) * 100 / ping->packets_transmitted) != 100)
		printf("round-trip min/avg/max/stddev = %.3f/%.3f/%.3f/%.3f ms\n", ping->min_time, ping->total_time / ping->packets_received, ping->max_time, ping->stddev);
}

void	printPing(t_answer *ping)
{
	if (!ping->timeout)
		printf("%d bytes from %s (%s): icmp_seq=%d ttl=%d time=%.3f ms\n", ping->size, ping->hostname, ping->selfAddress, ping->icmp_ind, ping->ttl, ping->time);
	else if (ping->timeout && !ping->verbose && !ping->unreachable)
		printf("Request timeout for icmp_seq %d\n", ping->icmp_ind);
	else if (ping->timeout && !ping->verbose && ping->unreachable)
		printf("%d bytes from %s (%s): Destination host unreachable\n", ping->size, ping->hostname, ping->selfAddress);	
	else if (ping->timeout && ping->verbose)
		printVerbosePing(ping);
}

void	printVerbosePing(t_answer *ping)
{
	if (!ping->ip || !ping->icmp)
	{
		printf("ft_ping: Destination unreachable\n");
		return;
	}
	ping->icmp_type = 0;
	ping->icmp_code = 0;
	ping->icmp_type = ping->icmp->type;
	ping->icmp_code = ping->icmp->code;
	uint16_t off = 0;
    uint8_t flags = 0;
    uint16_t frag = 0;
    uint16_t len = 0;
    uint16_t id = 0;
    uint16_t cksum = 0;
	
	if (ping->ip)
	{	
		off  = ping->ip->ip_off ? ntohs(ping->ip->ip_off) : 0;
		flags = off >> 13;         // top 3 bits
		frag  = off & 0x1FFF;      // low 13 bits
		len   = ping->ip->ip_len ? ntohs(ping->ip->ip_len) : 0;
		id    = ping->ip->ip_id ? ntohs(ping->ip->ip_id) : 0;
		cksum = ping->ip->ip_sum ? ntohs(ping->ip->ip_sum) : 0;
	}
	
	ping->verboseError = true;
	char *dst = charIp_to_hex(ping->addressN);
	char *src = charIp_to_hex(ping->selfAddress);
	
	char *description = get_icmp_description(ping->icmp_type, ping->icmp_code);
	printf("%d bytes from %s (%s): %s\n", ping->size, ping->hostname, ping->selfAddress, description ? description : "Destination host unreachable");
	
	printf("IP Hdr Dump :\n");
	printf("%-1x%-1x %-2x 00%-2x %-4x %-1x%-1x%-2x%-2x%-2x %s %s\n", ping->ip->ip_v, ping->ip->ip_hl, ping->ip->ip_tos, 64, id, flags, frag, ping->ttl, ping->ip->ip_p, cksum, src, dst);
	
	printf("Vr   HL   TOS  Len    ID     Flg   off   TTL    Pro    cks         Src	        Dst	        Data\n");
	printf("%-4u %-4u %-4u %-6u %-5u   %-4u %-5u %-4u    %-2u   %#6x  %-15s%-15s\n", ping->ip->ip_v, ping->ip->ip_hl, ping->ip->ip_tos, len, id, flags, frag, ping->ttl, ping->ip->ip_p, cksum, ping->selfAddress,ping->addressN);
	
	printf("ICMP : type %d, code %d, size %d, id 0x%-4x, seq 0x%-4x\n", ping->icmp_type, ping->icmp_code, PACKET_SIZE, ping->id, ping->icmp_ind);
	free(src);
	free(dst);
}


void	printHelpPing(void)
{
	printf("usage: ping [options] destination\nSend ICMP ECHO_REQUEST packets to network hosts.\n\n Options valid for all request types:\n\n-v                     verbose output\n--ttl=N                specify N as time-to-live\n--interval=NUMBER      wait NUMBER seconds between sending each packet\n--count=n              stop after sending count ECHO_REQUEST packets\n--tos=NUM              set type of service (TOS) to NUM\n-?                     give this help list\n");
}

char *get_icmp_description(int type, int code) {
    icmp_code_description_t *p;
    for (p = icmp_code_description; p < icmp_code_description + NITEMS(icmp_code_description); p++) {
        if (p->type == type && p->code == code) {
            return p->diag;
        }
    }
    return NULL;
}

void	calculate_stddev(t_answer *ping)
{
	double mean = 1;
	double var = 1;
	if (ping->packets_received > 0)
	{
		mean = ping->total_time / ping->packets_received;
		var = ping->total_time_squared / ping->packets_received - mean * mean;
		ping->stddev = sqrt(var);
	}
	else
	{
		mean = 0;
		var = 0;
		ping->stddev = 0;
	}
}

char *charIp_to_hex(char *addr)
{
    if (!addr)
        return NULL;
    char *returned = malloc(10);
    if (!returned)
	    return NULL;

	memset(returned, 0, 10);
    unsigned int a, b, c, d;
    if (sscanf(addr, "%u.%u.%u.%u", &a, &b, &c, &d) != 4) {
        free(returned);
        return NULL;
    }
    
    if (a > 255 || b > 255 || c > 255 || d > 255) {
        free(returned);
        return NULL;
    }
    sprintf(returned, "%02x%02x %02x%02x", a, b, c, d);
    return returned;
}