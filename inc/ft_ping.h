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
# include <net/if.h>
# include <netinet/ip.h>
# include <math.h>

// DEFINES

# define PACKET_SIZE 64
# define ICMP_HEADER_SIZE 8
# define DATA_SIZE (PACKET_SIZE - ICMP_HEADER_SIZE)

// STUCTURES

typedef struct s_ping
{
	bool verbose;
	char *address;
	char *option;
	char *option2;
	bool gotAddress;
	int  gotFlag;
	bool error;
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
	char *verbose;
	struct sockaddr_in dest;
    unsigned int packets_transmitted;
    unsigned int packets_received;
    double min_time;
    double max_time;
    double total_time;
    double mdev;
	double med_time;
}	t_answer;

struct icmp_header {
    uint8_t  type;
    uint8_t  code;
    uint16_t checksum;
    uint16_t identifier;
    uint16_t sequence;
};

// PARSING
t_ping *parseInputs(char **argv, int argc);
bool isFlag(char *str);
bool	isValidFlag(char *str);
bool	isAddress(char *str);


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

// SIGNALS
void    handleSignal(int signal);

// FREE
void	freeDuringInit(t_answer *answer, t_ping *ping);

#endif