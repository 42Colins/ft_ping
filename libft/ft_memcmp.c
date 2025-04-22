/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cprojean <cprojean@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 13:12:20 by cprojean          #+#    #+#             */
/*   Updated: 2022/11/28 17:36:45 by cprojean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t	i;
	char	*array;
	char	*string;

	array = (char *)s1;
	string = (char *)s2;
	i = 0;
	while (i < n)
	{
		if (array[i] != string[i])
			return ((unsigned char)array[i] - (unsigned char)string[i]);
		i++;
	}
	return (0);
}
