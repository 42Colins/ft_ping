#include "ft_ping.h"

t_ping *parseInputs(char **argv, int argc)
{
	t_ping *parsee;
	parsee = malloc(sizeof(t_ping));
	parsee->gotAddress = 0;	
	parsee->gotFlag = 0;
	parsee->error = 0;
	parsee->verbose = false;
	for (int i = 1; i < argc; i++)
	{
		if (!isValidFlag(argv[i]) && !isAddress(argv[i]))
			if (!parsee->gotAddress && !isFlag(argv[i]))
			{	
				dprintf(2, "ft_ping : cannot resolve %s : Unknown host\n", argv[i]);
				parsee->error = 1;
			}
			else
			{
				dprintf(2, "ft_ping : unknown flag %s\n", argv[i]);
				parsee->error = 1;
			}
		else
			if (isValidFlag(argv[i]))
			{
				if (argv[i][1] == '?')
				{
					printHelpPing();
					free(parsee);
					return (NULL);
				}
				if (argv[i][1] == 'v')
					parsee->verbose = true;
				if (parsee->gotFlag == 0)
				{
					parsee->option = argv[i];
				}
				else if (parsee->gotFlag == 1)
				{
					parsee->option2 = argv[i];
				}
				else
				{
					dprintf(2, "ft_ping : too much options \n");
					parsee->error = 1;
				}
				parsee->gotFlag += 1;
			}
			else if (isAddress(argv[i]))
				parsee->address = argv[i];
				
	}
	if (parsee->error == 1)
	{
		free (parsee);
		return NULL;
	}
	return parsee;
}

bool	isFlag(char *str)
{
	if (str[0] == '-')
		return true;
	return false;
}

bool	isValidFlag(char *str)
{
	if (!str)
		return false;
	if (strlen(str) > 2)
		return false;
	if (str[0] != '-')
		return false;
	if (str[1] == 'v' || str[1] == '?')
		return true;
	return false;
}

bool	isAddress(char *str)
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