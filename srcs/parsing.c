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

    while (i < argc) {
        if (argv[i][0] == '-') {
            if (strcmp(argv[i], "-v") == 0) {
                verbose = true;
            }
            if (strcmp(argv[i], "-?") == 0){
                printHelpPing();
                return NULL;
            }
			if (strncmp(argv[i], "--ttl=", 6) == 0)
			{
				if (strlen(argv[i]) > 6 && isTtl(argv[i]))
				{
					ttl = atoi(&argv[i][6]);
					if (ttl < 1)
						printf("ft_ping: option value too small: %d\n", ttl);
					else if (ttl > 255)
						printf("ft_ping: option value too big: %d\n", ttl);
				}
				else if (strlen(argv[i]) > 6 && !isTtl(argv[i]))
				{
					printf("ft_ping: invalid ttl: %s\n", &argv[i][5]);
					return NULL;
				}
				else if (strlen(argv[i]) == 5)
					printf("ft_ping: option value too small:\n");
			}
			if (strncmp(argv[i], "--interval=", 11) == 0)
			{
				if (strlen(argv[i]) > 11 && isInterval(argv[i]))
					interval = atof(&argv[i][11]);
				else if (strlen(argv[i]) > 11 && !isInterval(argv[i]))
					printf("ft_ping: invalid interval: %s\n", &argv[i][11]);
			}
			if (strncmp(argv[i], "--count=", 8) == 0)
			{
				if (strlen(argv[i]) > 8 && isCount(argv[i]))
					count = (unsigned int) atoi(&argv[i][8]);
				else if (strlen(argv[i]) > 8 && !isCount(argv[i]))
					printf("ft_ping: invalid count: %s\n", &argv[i][8]);
				else if (strlen(argv[i]) == 8)
					continue;
			}
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
    parsee->verbose = verbose;
    parsee->address = address;
    parsee->gotAddress = 1;
    parsee->error = 0;
	parsee->ttl = ttl;
	parsee->interval = interval;
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

bool isTtl(char *str)
{
	if (strlen(str) > 5)
	{
		for (unsigned long i = 6; i < strlen(str); i++)
		{
			if (!ft_isdigit(str[i]))
				return false;
		}
		return true;
	}
	else
		return false;
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

bool isCount(char *str)
{
	if (strlen(str) > 8)
	{
		for (unsigned long i = 8; i < strlen(str); i++)
		{
			if (!ft_isdigit(str[i]))
				return false;
		}
		return true;
	}
	else
		return false;
}