/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cprojean <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 13:17:39 by cprojean          #+#    #+#             */
/*   Updated: 2022/11/28 16:42:48 by cprojean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			index;
	unsigned char	*array;
	unsigned char	*string;

	array = (unsigned char *)s1;
	string = (unsigned char *)s2;
	index = 0;
	if (n == 0)
		return (0);
	while (((array[index]) || (string[index])) && ((size_t) index != n))
	{
		if (array[index] != string[index])
			return ((array[index] + '0') - (string[index] + '0'));
		index++;
	}
	return (0);
}
