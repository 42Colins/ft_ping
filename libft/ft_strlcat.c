/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cprojean <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 18:07:13 by cprojean          #+#    #+#             */
/*   Updated: 2022/11/15 18:14:28 by cprojean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	int		index;
	size_t	start;

	index = 0;
	if (dstsize == 0)
		return (ft_strlen(src));
	start = ft_strlen(dst);
	if (start > dstsize)
		return (ft_strlen(src) + dstsize);
	while ((start + index < dstsize - 1) && (src[index] != '\0'))
	{
		dst[start + index] = src[index];
		index++;
	}
	dst[index + start] = '\0';
	return (start + ft_strlen(src));
}
