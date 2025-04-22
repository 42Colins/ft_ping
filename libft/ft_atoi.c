/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cprojean <cprojean@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 13:07:22 by cprojean          #+#    #+#             */
/*   Updated: 2022/11/30 15:00:37 by cprojean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_filler(long answer, const char *str, int sign, int index)
{
	while (('0' <= str[index] && str[index] <= '9'))
	{
		if (answer != ((answer * 10) + (str[index] - '0')) / 10 && sign == -1)
			return (0);
		if (answer != ((answer * 10) + (str[index] - '0')) / 10 && sign == 1)
			return (-1);
		answer = answer * 10 + str[index] - 48;
		index++;
	}
	return (sign * answer);
}

int	ft_atoi(const char *str)
{
	int		index;
	int		sign;
	long	answer;

	answer = 0;
	sign = 1;
	index = 0;
	while ((9 <= str[index] && str[index] <= 13) || (str[index] == ' '))
		index++;
	if (str[index] == '-')
	{
		sign = -1;
		index++;
	}
	else if (str[index] == '+')
		index++;
	return (ft_filler(answer, str, sign, index));
}
