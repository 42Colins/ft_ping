#include "ft_ping.h"

t_ping *parseInputs(char **argv, int argc)
{
    t_ping *parsee;
    bool verbose = false;
    char *address = NULL;
    int i = 1;
	int ttl = 64;
	int interval = 1;
	int count = 0;
	int tos = 0;
	unsigned int size;
	bool isSize = false;
    while (i < argc) {
        if (argv[i][0] == '-') {
            if (strcmp(argv[i], "-v") == 0) {
                verbose = true;
            }
            else if (strcmp(argv[i], "-?") == 0){
                printHelpPing();
                return NULL;
            }
			else if (strncmp(argv[i], "--ttl=", 6) == 0)
			{
				if (strlen(argv[i]) > 6 && isNumber(&argv[i][6]))
				{
					ttl = atoi(&argv[i][6]);
					if (ttl < 1)
						printf("ft_ping: option value too small: %d\n", ttl);
					else if (ttl > 255)
						printf("ft_ping: option value too big: %d\n", ttl);
				}
				else if (strlen(argv[i]) > 6 && !isNumber(&argv[i][6]))
				{
					printf("ft_ping: invalid ttl: %s\n", &argv[i][6]);
					return NULL;
				}
				else if (strlen(argv[i]) == 5)
					printf("ft_ping: option value too small:\n");
			}
			else if (strncmp(argv[i], "--interval=", 11) == 0)
			{
				if (strlen(argv[i]) > 11 && isInterval(argv[i]))
					interval = atof(&argv[i][11]);
				else if (strlen(argv[i]) > 11 && !isInterval(argv[i]))
					printf("ft_ping: invalid interval: %s\n", &argv[i][11]);
			}
			else if (strncmp(argv[i], "--count=", 8) == 0)
			{
				if (strlen(argv[i]) > 8 && isNumber(&argv[i][8]))
					count = (unsigned int) atoi(&argv[i][8]);
				else if (strlen(argv[i]) > 8 && !isNumber(&argv[i][8]))
					printf("ft_ping: invalid count: %s\n", &argv[i][8]);
				else if (strlen(argv[i]) == 8)
					continue;
			}
			else if (strncmp(argv[i], "--tos=", 6) == 0)
			{
				if (strlen(argv[i]) > 6 && isNumber(&argv[i][6]))
				{
					tos = atoi(&argv[i][6]);
					if (tos < 0 || tos > 255)
						printf("ft_ping: option value too big: %s\n", &argv[i][6]);
				}
				else if (strlen(argv[i]) > 6 && !isNumber(&argv[i][6]))
					printf("ft_ping: invalid value %s\n", &argv[i][6]);
			}
			else if (strncmp(argv[i], "--size=", 7) == 0)
			{
				if (strlen(argv[i]) > 7 && isNumber(&argv[i][7]))
				{
					isSize = true;
					size = atoi(&argv[i][7]);
					if (size > 65507)
						printf("ft_ping: option value too big: %s\n", &argv[i][7]);
				}
				else if (strlen(argv[i]) > 7 && !isNumber(&argv[i][7]))
					printf("ft_ping: invalid value %s\n", &argv[i][7]);
			}
			else if (strcmp(argv[i], "--help") == 0)
				printHelpPing();
			else
				printf("ping: unrecognized option %s\n", argv[i]);
        }
        else if (!address) {
            address = argv[i];
        }
        i++;
    }
    if (!address) {
        dprintf(2, "ft_ping: missing host operand\n");
        return NULL;
    }
    if (!isAddress(address)) {
        dprintf(2, "ft_ping : cannot resolve %s : Unknown host\n", address);
        return NULL;
    }
    parsee = malloc(sizeof(t_ping));
    if (!parsee)
        {return NULL;}
	parsee->isCount = false;
	if (count > 0)
	{
		parsee->isCount = true;
		parsee->count = count;
	}
	if (tos > 0)
		parsee->tos = tos;
    parsee->verbose = verbose;
    parsee->address = address;
    parsee->gotAddress = 1;
    parsee->error = 0;
	parsee->ttl = ttl;
	parsee->interval = interval;
	if (isSize)
		parsee->size = size + ICMP_HEADER_SIZE;
	else
		parsee->size = PACKET_SIZE;
    return parsee;
}

bool isAddress(char *str)
{
    struct addrinfo hints;
    struct addrinfo *res;

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;

    int status = getaddrinfo(str, NULL, &hints, &res);
    if (status != 0)
        return 0;

    freeaddrinfo(res);
    return 1;
} 

bool isInterval(char *str)
{
	int dot = 0;
	if (strlen(str) > 11)
	{
		for (unsigned long i = 11; i < strlen(str); i++)
		{
			if (!ft_isdigit(str[i]))
			{
				if (str[i] == '.')
				{
					if (dot > 0)
						return false;
					dot++;
					continue;
				}	
				return false;
			}
		}
		return true;
	}
	else
		return false;
}

bool isNumber(char *str)
{
	if (strlen(str) > 0)
	{
		for (unsigned long i = 0; i < strlen(str); i++)
		{
			if (!ft_isdigit(str[i]))
				return false;
		}
		return true;
	}
	else
		return false;
}