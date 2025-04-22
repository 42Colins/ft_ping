/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cprojean <cprojean@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 11:54:32 by cprojean          #+#    #+#             */
/*   Updated: 2022/11/28 17:36:20 by cprojean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*array;
	unsigned char	cast;

	cast = (unsigned char) c;
	array = (unsigned char *) s;
	i = 0;
	while (i < n)
	{
		if (array[i] == cast)
			return (&array[i]);
		i++;
	}
	return (NULL);
}
