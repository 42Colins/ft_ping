/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cprojean <cprojean@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 15:41:24 by cprojean          #+#    #+#             */
/*   Updated: 2022/11/30 18:11:16 by cprojean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	index;
	size_t	runner;

	index = 0;
	runner = 0;
	if (ft_strlen(needle) == 0)
		return ((char *)&haystack[0]);
	while (haystack[index])
	{
		while ((haystack[index + runner] == needle[runner])
			&& ((size_t)runner + index < len))
		{
			runner++;
			if (runner == ft_strlen(needle))
				return ((char *)&haystack[index]);
		}
		runner = 0;
		index++;
	}
	return (NULL);
}
