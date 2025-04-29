/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cprojean <cprojean@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 10:40:38 by cprojean          #+#    #+#             */
/*   Updated: 2022/11/28 17:37:03 by cprojean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	i;
	char	*str;
	char	*array;

	i = 0;
	if (src == NULL && dst == NULL)
		return (0);
	array = (char *) src;
	str = dst;
	while (i < n)
	{
		str[i] = (char)array[i];
		i++;
	}
	return (&str[0]);
}
