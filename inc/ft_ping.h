#ifndef FT_PING_H
# define FT_PING_H

# include "libft.h"
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <stdbool.h>
# include <netdb.h>
# include <arpa/inet.h>
# include <sys/time.h>
# include <sys/ioctl.h>
# include <sys/param.h>
# include <net/if.h>
# include <netinet/ip.h>
# include <math.h>
# include <unistd.h>
# include <getopt.h>

// Argument parser structure
struct arguments {
    bool verbose;
    char *address;
};

// ICMP TYPES AND CODES BECAUSE THE NETINET/IP_ICMP.H IS NOT WORKING THE SAME ON MACOS

#define ICMP_ECHOREPLY                0        /* Echo Reply                        */
#define ICMP_DEST_UNREACH        3        /* Destination Unreachable        */
#define ICMP_SOURCE_QUENCH        4        /* Source Quench                */
#define ICMP_REDIRECT                5        /* Redirect (change route)        */
#define ICMP_ECHO                8        /* Echo Request                        */
#define ICMP_TIME_EXCEEDED        11        /* Time Exceeded                */
#define ICMP_PARAMETERPROB        12        /* Parameter Problem                */
#define ICMP_TIMESTAMP                13        /* Timestamp Request                */
#define ICMP_TIMESTAMPREPLY        14        /* Timestamp Reply                */
#define ICMP_INFO_REQUEST        15        /* Information Request                */
#define ICMP_INFO_REPLY                16        /* Information Reply                */
#define ICMP_ADDRESS                17        /* Address Mask Request                */
#define ICMP_ADDRESSREPLY        18        /* Address Mask Reply                */
#define NR_ICMP_TYPES                18
/* Codes for UNREACH. */
#define ICMP_NET_UNREACH        0        /* Network Unreachable                */
#define ICMP_HOST_UNREACH        1        /* Host Unreachable                */
#define ICMP_PROT_UNREACH        2        /* Protocol Unreachable                */
#define ICMP_PORT_UNREACH        3        /* Port Unreachable                */
#define ICMP_FRAG_NEEDED        4        /* Fragmentation Needed/DF set        */
#define ICMP_SR_FAILED                5        /* Source Route failed                */
#define ICMP_NET_UNKNOWN        6
#define ICMP_HOST_UNKNOWN        7
#define ICMP_HOST_ISOLATED        8
#define ICMP_NET_ANO                9
#define ICMP_HOST_ANO                10
#define ICMP_NET_UNR_TOS        11
#define ICMP_HOST_UNR_TOS        12
#define ICMP_PKT_FILTERED        13        /* Packet filtered */
#define ICMP_PREC_VIOLATION        14        /* Precedence violation */
#define ICMP_PREC_CUTOFF        15        /* Precedence cut off */
#define NR_ICMP_UNREACH                15        /* instead of hardcoding immediate value */
/* Codes for REDIRECT. */
#define ICMP_REDIR_NET                0        /* Redirect Net                        */
#define ICMP_REDIR_HOST                1        /* Redirect Host                */
#define ICMP_REDIR_NETTOS        2        /* Redirect Net for TOS                */
#define ICMP_REDIR_HOSTTOS        3        /* Redirect Host for TOS        */
/* Codes for TIME_EXCEEDED. */
#define ICMP_EXC_TTL                0        /* TTL count exceeded                */
#define ICMP_EXC_FRAGTIME        1        /* Fragment Reass time exceeded        */

// DEFINES

# define PACKET_SIZE 64
# define ICMP_HEADER_SIZE 8
# define DATA_SIZE (PACKET_SIZE - ICMP_HEADER_SIZE)

// STUCTURES

typedef struct s_ping
{
	int  ttl;
	bool verbose;
	bool isCount;
	char *address;
	char *option;
	char *option2;
	bool gotAddress;
	int  gotFlag;
	bool error;
	double  interval;
	unsigned int  count;
}	t_ping;

typedef struct s_answer
{
	bool timeout;
	unsigned int icmp_ind;
	int socketFd;
	int	bytes_sent;
	char *packet;
	char *address;
	char *addressN;
	char *reversednsAddress;
	struct icmp_header *icmp;
	int received;
	unsigned long packet_loss;
	int ttl;
	long start_time;
	double time;
	double *time_array;
	bool verbose;
	bool verboseError;
	struct sockaddr_in dest;
    unsigned int packets_transmitted;
    unsigned int packets_received;
    double min_time;
    double max_time;
    double total_time;
	double total_time_squared;
    double mdev;
	double med_time;
	double stddev;
	char *ip_hdr;
	struct ip *ip;
    uint16_t id;
	int  icmp_type;
	int  icmp_code;
}	t_answer;

struct icmp_header {
    uint8_t  type;
    uint8_t  code;
    uint16_t checksum;
    uint16_t identifier;
    uint16_t sequence;
};

typedef struct icmp_codes_s {
    int type;
    int code;
    char *diag;
} icmp_codes_t;

// PARSING
t_ping *parseInputs(char **argv, int argc);
bool	isTtl(char *str);
bool	isAddress(char *str);
bool	isInterval(char *str);
bool	isCount(char *str);

// TIME
bool	get_time(t_answer *ping);
bool	start_time(t_answer *ping);
void    set_round_trip(t_answer *answer);

// PRINT
void	initPrint(t_answer *ping);
void	endPrint(t_answer *ping);
void	printPing(t_answer *ping);
void	printVerbosePing(t_answer *ping);
void	printHelpPing(void);
char	*get_icmp_description(int type, int code);
void	calculate_stddev(t_answer *ping);

// INIT
void    setSocket(t_answer *answer, t_ping *ping);
void    getAddress(t_answer *answer, t_ping *ping);
void    getDnsAddress(t_answer *answer, t_ping *ping);
t_answer *initPing(t_ping *ping, t_answer *answer);
void    initAnswer(t_answer *answer, t_ping *ping);

// PING
unsigned short checksum(void *b, int len);
void	sendPing(t_ping *ping, t_answer *answer);
void	receivePing(t_ping *ping, t_answer *answer);
void    checkIcmpType(t_answer *answer);

// SIGNALS
void    handleSignal(int signal);

// FREE
void	freeDuringInit(t_answer *answer, t_ping *ping);
void	exitOnCount(t_answer *answer);

#endif