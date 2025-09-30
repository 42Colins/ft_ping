#ifndef FT_PING_H
# define FT_PING_H

# include "libft.h"
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <stdbool.h>
# include <netdb.h>
# include <sys/time.h>
# include <sys/ioctl.h>
# include <sys/param.h>
# include <net/if.h>
# include <netinet/ip.h>
# include <netinet/ip_icmp.h>
# include <arpa/inet.h>
# include <math.h>
# include <unistd.h>
# include <getopt.h>
# include <ifaddrs.h>
# include <errno.h>

// Argument parser structure
struct arguments {
    bool verbose;
    char *address;
};

// ICMP TYPES AND CODES BECAUSE THE NETINET/IP_ICMP.H IS NOT WORKING THE SAME ON MACOS

#define ICMP_ECHOREPLY                0        
#define ICMP_DEST_UNREACH        3        
#define ICMP_SOURCE_QUENCH        4        
#define ICMP_REDIRECT                5       
#define ICMP_ECHO                8        
#define ICMP_TIME_EXCEEDED        11        
#define ICMP_PARAMETERPROB        12        
#define ICMP_TIMESTAMP                13        
#define ICMP_TIMESTAMPREPLY        14        
#define ICMP_INFO_REQUEST        15        
#define ICMP_INFO_REPLY                16        
#define ICMP_ADDRESS                17                       
#define ICMP_ADDRESSREPLY        18                       
#define NR_ICMP_TYPES                18

#define ICMP_NET_UNREACH        0        
#define ICMP_HOST_UNREACH        1        
#define ICMP_PROT_UNREACH        2        
#define ICMP_PORT_UNREACH        3        
#define ICMP_FRAG_NEEDED        4       
#define ICMP_SR_FAILED                5                        
#define ICMP_NET_UNKNOWN        6
#define ICMP_HOST_UNKNOWN        7
#define ICMP_HOST_ISOLATED        8
#define ICMP_NET_ANO                9
#define ICMP_HOST_ANO                10
#define ICMP_NET_UNR_TOS        11
#define ICMP_HOST_UNR_TOS        12
#define ICMP_PKT_FILTERED        13        
#define ICMP_PREC_VIOLATION        14        
#define ICMP_PREC_CUTOFF        15         
#define NR_ICMP_UNREACH                15       

#define ICMP_REDIR_NET                0        
#define ICMP_REDIR_HOST                1        
#define ICMP_REDIR_NETTOS        2       
#define ICMP_REDIR_HOSTTOS        3     

#define ICMP_EXC_TTL                0                        
#define ICMP_EXC_FRAGTIME        1       
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
	int  size;
	char *address;
	char *option;
	char *option2;
	bool gotAddress;
	int  gotFlag;
	int tos;
	bool isTos;
	bool error;
	double  interval;
	unsigned int  count;
}	t_ping;

typedef struct s_answer
{
	unsigned int count;
	bool isCount;
	unsigned int done;
	bool unreachable;
	int  tos;
	bool isTos;
	int  size;
	bool sent;
	bool timeout;
	unsigned int icmp_ind;
	int socketFd;
	int	bytes_sent;
	char *packet;
	char *address;
	char *addressN;
	char *selfAddress;
	char *hostname;
	char *sender_address;
	struct icmp_header *icmp;
	int received;
	unsigned long packet_loss;
	int ttl;
	int received_ttl;
	double start_time;
	double time;
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
	struct ip *ip;
    uint16_t id;
	int  icmp_type;
	int  icmp_code;
	bool ttlExceeded;
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
bool	isAddress(char *str);
bool	isInterval(char *str);
bool	isNumber(char *str);
bool isRoot(void);


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
char 	*charIp_to_hex(char *addr);

// INIT
void    setSocket(t_answer *answer, t_ping *ping);
void    getAddress(t_answer *answer, t_ping *ping);
void    getSelfAddress(t_answer *answer, t_ping *ping);
t_answer *initPing(t_ping *ping, t_answer *answer);
void    initAnswer(t_answer *answer, t_ping *ping);

// PING
unsigned short checksum(void *b, int len);
void    sendPing(t_answer *answer);
void	receivePing(t_answer *answer);
void    checkIcmpType(t_answer *answer);

// SIGNALS
void    handleSignal(int signal);

// FREE
void	freeDuringInit(t_answer *answer, t_ping *ping);
void	exitOnCount(t_answer *answer);

#endif