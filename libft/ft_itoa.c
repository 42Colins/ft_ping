/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cprojean <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 18:27:44 by cprojean          #+#    #+#             */
/*   Updated: 2022/11/28 16:41:08 by cprojean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_count_size(int n)
{
	int	count;

	count = 0;
	if (n < 0)
	{
		count++;
		n = n * -1;
	}
	while (n >= 10)
	{
		n = n / 10;
		count++;
	}
	return (count);
}

char	*ft_array_fill(char *array, int size, int n)
{
	int		index;
	int		pos;
	int		count;

	count = size;
	index = 0;
	pos = 0;
	if (n < 0)
	{
		n = n * -1;
		array[index] = '-';
		index++;
	}
	while (n >= 10)
	{
		pos = n % 10;
		array[count - 1] = pos + '0';
		n = n / 10;
		index++;
		count--;
	}
	array[count - 1] = n + '0';
	array[index + 1] = '\0';
	return (array);
}

char	*ft_itoa(int n)
{
	char	*array;
	int		count;

	count = ft_count_size(n) + 1;
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	array = malloc(sizeof(char) * count + 1);
	if (!array)
		return (NULL);
	return (ft_array_fill(array, count, n));
}
